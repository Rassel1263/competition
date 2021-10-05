#include "DXUT.h"
#include "Obstacle.h"

Obstacle::Obstacle(D3DXVECTOR2 pos, Type type)
{
	this->pos = pos;
	this->type = type;

	if(type == Type::GARABAGE)
	{ 
		spr.LoadAll(L"Assets/Sprites/Obstacle/Garbage/" + std::to_wstring(nowScene->GetRandNum(1, 2)), 0.05f, true);
		CreateCollider(D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), L"obstacle");
	}
	else if (type == Type::MINE)
	{
		range.LoadAll(L"Assets/Sprites/Obstacle/mineRange.png");

		spr.LoadAll(L"Assets/Sprites/Obstacle/Mine/", 0.05f, true);
		CreateCollider(D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), L"obstacle");
	}
	else
	{
		int index = nowScene->GetRandNum(0, 3);
		spr.LoadAll(L"Assets/Sprites/Obstacle/rock/" + std::to_wstring(index) + L".png");

		if (index == 0)
			CreateCollider(D3DXVECTOR2(-220, -120), D3DXVECTOR2(220, 120), L"obstacle");
		else if(index == 1)
			CreateCollider(D3DXVECTOR2(-220, -140), D3DXVECTOR2(220, 140), L"obstacle");
		else if(index == 2)
			CreateCollider(D3DXVECTOR2(-200, -120), D3DXVECTOR2(150, 120), L"obstacle");
		else
			CreateCollider(D3DXVECTOR2(-40, -40), D3DXVECTOR2(40, 40), L"obstacle");
	}
}

void Obstacle::Update(float deltaTime)
{
	if (nowScene->spawnBoss)
		destroy = true;

	if (pos.y < Camera::GetInstance().cameraPos.y - 1000)
	{
		if (type == Type::GARABAGE)
			nowScene->obstacleManager.DeleteGarbage(this);

		destroy = true;
	}

	spr.Update(deltaTime);
}

void Obstacle::Render()
{
	ri.pos = pos;

	if (type == Type::MINE)
		range.Render(ri);

	spr.Render(ri);

	Object::Render();
}

void Obstacle::OnCollision(Collider& coli)
{
	if (coli.tag == L"player")
	{
		if (type == Type::MINE)
		{
			nowScene->obm.AddObject(new Effect(L"onexplode", pos, D3DXVECTOR2(0.6, 0.6), D3DXVECTOR2(0.5, 0.5), 1, true , 0.05f));
			destroy = true;
		}
	}

	if (coli.tag == L"playerbullet" || coli.tag == L"enemybullet")
	{
		if (type == Type::GARABAGE)
		{
			if (static_cast<Bullet*>(coli.obj)->type == Bullet::Type::TORPEDO)
			{
				nowScene->obm.AddObject(new Item(pos, nowScene->GetRandNum(0, 5)));

				nowScene->obstacleManager.DeleteGarbage(this);
				destroy = true;
			}
		}
	}
}

void ObstacleManager::DeleteGarbage(Obstacle* garbage)
{
	auto gf = std::find(garbages.begin(), garbages.end(), garbage);
	if(gf != garbages.end())
		garbages.erase(gf);
}

void ObstacleManager::Init(float gIntraval, float rInterval)
{
	this->gInterval = gIntraval;
	this->rInterval = rInterval;
}

void ObstacleManager::Spawner(float playerDistance)
{
	gDistance += playerDistance;
	rDistance += playerDistance;

	if (gDistance >= gInterval)
	{
		Obstacle* garbage;
		nowScene->obm.AddObject(garbage = new Obstacle(nowScene->player->pos + D3DXVECTOR2(nowScene->GetRandNum(-500, 500), 1000), Obstacle::Type::GARABAGE));
		garbages.push_back(garbage);
		gDistance = 0.0f;
	}

	if (rDistance >= rInterval)
	{
		nowScene->obm.AddObject(new Obstacle(nowScene->player->pos + D3DXVECTOR2(nowScene->GetRandNum(-1200, 1200), 1000), Obstacle::Type::ROCK));
		rDistance = 0.0f;
	}
}
