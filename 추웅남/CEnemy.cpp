#include "DXUT.h"
#include "CEnemy.h"

CEnemy::CEnemy(D3DXVECTOR2 pos)
{
	team = L"enemy";

	this->pos = pos;
	this->target = nowScene->player;

	turnSpeed = D3DXToRadian(10);

	nowScene->miniMap->AddMiniObj(MiniMap::MiniInfo{ MiniTag::ENEMY, this });

	layer = 5;
}

void CEnemy::Update(float deltaTime)
{
	if (nowScene->spawnBoss)
	{
		if (type != Type::BigFly && type != Type::BigFloat)
		{
			nowScene->obm.AddObject(new Effect(L"onexplode", pos, D3DXVECTOR2(0.5, 0.5), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
			CEnemy::Destroy();
		}
	}

	if(attackTimer <= attackTime)
		attackTimer += deltaTime;

	Unit::Update(deltaTime);
}

void CEnemy::Render()
{
	ri.pos = pos;

	if (hit)
		colorShader->Render(colorShader, GetNowSprite(), ri);
	else
		GetNowSprite().Render(ri);

	Object::Render();
}

void CEnemy::OnCollision(Collider& coli)
{
	if (coli.tag == L"playerbullet")
	{
		auto pBullet = static_cast<Bullet*>(coli.obj);

		if (type == Type::Float && pBullet->type == Bullet::Type::MISSILE) return;
		if (type == Type::Fly && pBullet->type == Bullet::Type::TORPEDO) return;

		Hit(static_cast<Bullet*>(coli.obj)->damage);
	}

	
}

void CEnemy::Hit(float damage)
{
	if (hit) return;

	Unit::Hit(damage);

	if (ability.hp <= 0.0f)
		ability.hp = 0.0f;
}

void CEnemy::Move(float deltaTime)
{
	float targetAngle = D3DXToRadian(nowScene->GetAngleFromTarget(pos, target->pos));
	float diff = targetAngle - curRadian;

	if (type == Type::Fly)
	{
		if(attackTimer >= attackTime)
			turnTime += deltaTime;
	}
	else
		turnTime += deltaTime;

	if (turnTime >= 0.03f)
	{
		if (diff > D3DX_PI)
			diff -= D3DX_PI * 2;
		else if (diff < -D3DX_PI)
			diff += D3DX_PI * 2;

		if (diff > turnSpeed)
			curRadian += turnSpeed;
		else if (diff < -turnSpeed)
			curRadian -= turnSpeed;
		else
		{
			Attack(deltaTime);
			curRadian = targetAngle;
		}

		turnTime = 0.0f;
	}

	curRotate = -D3DXToDegree(curRadian) + 450;

	if(type == Type::BigFly)
		SetRotate(curRotate, 8);
	else
		SetRotate(curRotate, 24);


	pos += D3DXVECTOR2(cosf(curRadian), sinf(curRadian)) * ability.speed * deltaTime;
}

void CEnemy::Destroy()
{
	nowScene->enemyManager.SortEnemy(this, type);
	nowScene->miniMap->SortMiniObj(this);

	destroy = true;
}
