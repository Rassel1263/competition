#include "DXUT.h"
#include "Bullet.h"

Bullet::Bullet(std::wstring tag, D3DXVECTOR2 pos, D3DXVECTOR2 dir, float damage, float speed, Type type, float groundPos)
{
	this->tag = tag;
	this->type = type;
	this->pos = pos;
	this->groundPos = groundPos;

	this->damage = damage;
	this->speed = speed;
	this->dir = dir;

	layer = 1080 - (groundPos + 540);

	D3DXVec2Normalize(&this->dir, &dir);
	ri.rotate = -D3DXToDegree(atan2(dir.y, dir.x));

	if (tag == L"player")
	{
		spr.LoadAll(L"Assets/Sprites/bullet/playerbullet" + std::to_wstring(IntEnum(type)));

		if (type == Type::AIRSHOT)
			dir.y = 1.0f;

		if (type == Type::GRENADE)
			spr.LoadAll(L"Assets/Sprites/bullet/grenade.png");

		CreateCollider(D3DXVECTOR2(-80, -10), D3DXVECTOR2(80, 10), tag + L"bullet");
	}
	else if(tag == L"enemy")
	{
		if (type == Type::ROCK)
			spr.LoadAll(L"Assets/Sprites/bullet/enemyBullet");
		else if(type == Type::GOLDROCK)
			spr.LoadAll(L"Assets/Sprites/bullet/EnemybossRock");

		CreateCollider(D3DXVECTOR2(-10, -10), D3DXVECTOR2(10, 10), tag + L"bullet");
	}

	attackVec = { dir.x * 30, dir.y * 1000 };
}

void Bullet::Update(float deltaTime)
{
	if (pos.x > Camera::GetInstance().cameraPos.x + 960 || pos.x < Camera::GetInstance().cameraPos.x - 960 ||
		pos.y > Camera::GetInstance().cameraPos.y + 540|| pos.y < Camera::GetInstance().cameraPos.y - 540)
	{
		destroy = true;
	}

	if (pos.y <= groundPos)
	{
		if (type == Type::BASIC)
		{
			nowScene->obm.AddObject(new Effect(L"Player/Hit1", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));
			destroy = true;
		}
		else if (type == Type::GRENADE)
		{

			Camera::GetInstance().cameraQuaken = { 10, 10 };
			SoundManager::GetInstance().Play("Grenade");

			nowScene->obm.AddObject(new Effect(L"Player/explode", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));
			nowScene->obm.AddObject(new AttackCollider(tag, pos, D3DXVECTOR2(0, 0), D3DXVECTOR2(-150, -100), D3DXVECTOR2(150, 100), damage, D3DXVECTOR2(100, 0), 0.0f, groundPos, 0.1f));
			destroy = true;
		}
	}

	if (type == Type::GRENADE)
	{
		ri.rotate += 180 * deltaTime;
		dir.y -= deltaTime;
	}

	pos += dir * speed * deltaTime;
}

void Bullet::Render()
{
	ri.pos = pos;
	spr.Render(ri);
	Object::Render();
}

void Bullet::OnCollision(Collider & coli)
{
	if (tag == coli.tag) return;

	if (coli.tag == L"player" || coli.tag == L"enemy")
	{
		if (abs(groundPos - coli.obj->groundPos) >= 100) return;

		if (type == Type::GRENADE)
		{
			Camera::GetInstance().cameraQuaken = { 10, 10 };

			nowScene->obm.AddObject(new Effect(L"Player/explode", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));
			nowScene->obm.AddObject(new AttackCollider(tag, pos, D3DXVECTOR2(0, 0), D3DXVECTOR2(-150, -100), D3DXVECTOR2(150, 100), damage, D3DXVECTOR2(100, 0), 0.0f, groundPos, 0.1f));

			SoundManager::GetInstance().Play("Grenade");
			destroy = true;
		}
		else if (type != Type::SNIPER && type != Type::ESNIPER)
		{
			destroy = true;
			nowScene->obm.AddObject(new Effect(L"Player/Hit1", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));
		}
	}
}
