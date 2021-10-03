#include "DXUT.h"
#include "Bullet.h"

Bullet::Bullet(Unit* target, D3DXVECTOR2 pos, float damage, float speed, float angle, Type type, float startTime, bool horming)
{
	this->target = target;
	this->pos = pos;
	this->angle = angle;
	this->speed = speed;
	this->damage = damage;
	this->type = type;
	this->startTime = startTime;
	this->horming = horming;

	turnSpeed = D3DXToRadian(5);

	ri.rotate = -D3DXToDegree(angle) + 90;

	layer = 5;

	if (target == NULL)
	{
		tag = L"player";

		if (type == Type::MACHINE)
			spr.LoadAll(L"Assets/Sprites/bullet/machinegunBullet");
		else if (type == Type::NAVAL)
			spr.LoadAll(L"Assets/Sprites/bullet/navalgunBullet");

	}
	else if (target->team == L"enemy")
	{
		tag = L"player";

		if (type == Type::MACHINE)
			spr.LoadAll(L"Assets/Sprites/bullet/machinegunBullet");
		else if (type == Type::NAVAL)
			spr.LoadAll(L"Assets/Sprites/bullet/navalgunBullet");
		else if (type == Type::TORPEDO)
		{
			spr.LoadAll(L"Assets/Sprites/bullet/Torpedo");
			layer = 4;
		}
		else if (type == Type::MISSILE)
		{
			spr.LoadAll(L"Assets/Sprites/bullet/PlayerMissile");
			layer = 6;
		}
	}
	else if (target->team == L"player")
	{
		tag = L"enemy";

		if (type == Type::MACHINE)
			spr.LoadAll(L"Assets/Sprites/bullet/machinegunBullet");
		else if (type == Type::NAVAL)
			spr.LoadAll(L"Assets/Sprites/bullet/navalgunBullet");
		else if (type == Type::TORPEDO)
		{
			spr.LoadAll(L"Assets/Sprites/bullet/Torpedo");
			layer = 4;
		}
		else if (type == Type::MISSILE)
		{
			spr.LoadAll(L"Assets/Sprites/bullet/EnemyMissile");
			layer = 6;
		}
	}

	CreateCollider(D3DXVECTOR2(-10, -10), D3DXVECTOR2(10, 10), tag + L"bullet");

}

void Bullet::Update(float deltaTime)
{
	if (horming)
		HormingSystem(deltaTime);

	pos += D3DXVECTOR2(cosf(angle), sinf(angle)) * speed * deltaTime;

	if (pos.x >= Camera::GetInstance().cameraPos.x + 2000 || pos.x <= Camera::GetInstance().cameraPos.x - 2000 ||
		pos.y >= Camera::GetInstance().cameraPos.y + 1000 || pos.y <= Camera::GetInstance().cameraPos.y - 1000)
	{
		destroy = true;
	}

	spr.Update(deltaTime);
}

void Bullet::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}

void Bullet::OnCollision(Collider& coli)
{
	if (coli.tag == tag) return;

	if (coli.tag == L"player" || coli.tag == L"enemy")
	{
		if (coli.tag == L"enemy")
		{
			if (static_cast<CEnemy*>(coli.obj)->type == CEnemy::Type::Fly && type == Type::TORPEDO) return;
			if (static_cast<CEnemy*>(coli.obj)->type == CEnemy::Type::Float && type == Type::MISSILE) return;
		}

		if (type == Type::MACHINE)
			nowScene->obm.AddObject(new Effect(L"Hit_machinegun", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f, ri.rotate + 180));
		else if (type == Type::NAVAL)
		{
			SoundManager::GetInstance().Play("NavalHit");
			nowScene->obm.AddObject(new Effect(L"Hit_navalgun", pos, D3DXVECTOR2(2, 2), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f, ri.rotate + 180));
		}
		else if (type == Type::TORPEDO)
			nowScene->obm.AddObject(new Effect(L"Hit_Torpedo", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
		else if (type == Type::MISSILE)
			nowScene->obm.AddObject(new Effect(L"Hit_missile", pos, D3DXVECTOR2(2, 2), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f, ri.rotate + 180));

		destroy = true;
	}

	if (coli.tag == L"obstacle")
	{
		if (type != Type::MISSILE)
		{
			if (static_cast<Obstacle*>(coli.obj)->type == Obstacle::Type::ROCK)
			{
				if (type == Type::MACHINE)
					nowScene->obm.AddObject(new Effect(L"Hit_machinegun", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f, ri.rotate + 180));
				else if (type == Type::NAVAL)
				{
					SoundManager::GetInstance().Play("NavalHit");
					nowScene->obm.AddObject(new Effect(L"Hit_navalgun", pos, D3DXVECTOR2(2, 2), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f, ri.rotate + 180));
				}
				else if (type == Type::TORPEDO)
					nowScene->obm.AddObject(new Effect(L"Hit_Torpedo", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));

				destroy = true;
			}
		}
	}
}

void Bullet::HormingSystem(float deltaTime)
{
	if (startTime > 0.0f)
		startTime -= deltaTime;
	else
	{
		if (target->destroy)
			horming = false;

		turnTime += deltaTime;

		if (turnTime >= 0.01f)
		{
			float targetAngle = D3DXToRadian(nowScene->GetAngleFromTarget(pos, target->pos));
			float diff = targetAngle - angle;


			if (diff > D3DX_PI)
				diff -= D3DX_PI * 2;
			else if (diff < -D3DX_PI)
				diff += D3DX_PI * 2;

			if (diff > turnSpeed)
				angle += turnSpeed;
			else if (diff < -turnSpeed)
				angle -= turnSpeed;
			else
				angle = targetAngle;

			turnTime = 0.0f;
		}

		ri.rotate = -D3DXToDegree(angle) + 90;
	}
}
