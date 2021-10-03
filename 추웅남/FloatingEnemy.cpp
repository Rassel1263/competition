#include "DXUT.h"
#include "FloatingEnemy.h"

FloatingEnemy::FloatingEnemy(D3DXVECTOR2 pos) : CEnemy(pos)
{
	type = Type::Float;

	Resize(24);

	for (int i = 0; i < 24; ++i)
		GetSprite(i).LoadAll(L"Assets/Sprites/enemy/type1/move/" + std::to_wstring(i), 0.05f, true);

	attackTimer = attackTime;

	curRadian = D3DXToRadian(nowScene->GetAngleFromTarget(pos, target->pos));
	curRotate = -D3DXToDegree(curRadian) + 450;
	SetRotate(curRotate, 24);

	ability.SetAbility(30, 250);

	CreateCollider(D3DXVECTOR2(-100, -100), D3DXVECTOR2(100, 100), team);

	attackTime = 2.0f;
}

void FloatingEnemy::Update(float deltaTime)
{
	if (ability.hp <= 0.0f)
		Destroy();
	else
	{
		if (D3DXVec2Length(&(target->pos - pos)) < 400)
			ability.speed = 150;
		else
			ability.speed = 250;

		Move(deltaTime);
	}

	if (pos.y < nowScene->player->pos.y - 800)
	{
		nowScene->enemyManager.SortEnemy(this, type);
		nowScene->miniMap->SortMiniObj(this);
		destroy = true;
	}

	CEnemy::Update(deltaTime);
}

void FloatingEnemy::Render()
{
	CEnemy::Render();
}

void FloatingEnemy::Hit(float damage)
{
	if (hit) return;

	Unit::Hit(damage);

	if (ability.hp <= 0.0f)
	{
		SoundManager::GetInstance().Play("Explo");
		nowScene->obm.AddObject(new Effect(L"onexplode", pos, D3DXVECTOR2(0.5, 0.5), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
		nowScene->player->kill++;

		bCollider = false;
		GetNowSprite().LoadAll(L"Assets/Sprites/enemy/type1/sink/" + std::to_wstring(renderNum), 0.05f, false);
		GetNowSprite().Reset();

		nowScene->enemyManager.SortEnemy(this, type);
		nowScene->miniMap->SortMiniObj(this);

		ability.hp = 0.0f;
	}
}

void FloatingEnemy::Destroy()
{
	if (!GetNowSprite().bAnimation)
	{
		if (nowScene->GetRandNum(0, 3))
			nowScene->obm.AddObject(new Item(pos, nowScene->GetRandNum(0, 5)));
		else
			nowScene->obm.AddObject(new Obstacle(pos, Obstacle::Type::MINE));

		nowScene->destScore += nowScene->GetRandNum(1000, 2000);

		destroy = true;
	}
}

void FloatingEnemy::OnCollision(Collider& coli)
{
	CEnemy::OnCollision(coli);

	if (coli.tag == L"player")
	{
		if (type == Type::Float)
		{
			nowScene->obm.AddObject(new Effect(L"onexplode", pos, D3DXVECTOR2(0.5, 0.5), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
			SoundManager::GetInstance().Play("Explo");
			CEnemy::Destroy();
		}
	}

	if (coli.tag == L"obstacle")
	{
		if (type == Type::Float && static_cast<Obstacle*>(coli.obj)->type == Obstacle::Type::ROCK)
		{
			SoundManager::GetInstance().Play("Explo");
			nowScene->obm.AddObject(new Effect(L"onexplode", pos, D3DXVECTOR2(0.5, 0.5), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
			CEnemy::Destroy();
		}
	}
}

void FloatingEnemy::Attack(float deltaTime)
{
	if (attackTimer >= attackTime)
	{
		nowScene->obm.AddObject(new Bullet(target, pos, 10, 600, curRadian, Bullet::Type::TORPEDO));
		attackTimer = 0.0f;
	}
}

