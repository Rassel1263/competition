#include "DXUT.h"
#include "EnemyManager.h"

void EnemyManager::Init(float floatSpawnTime, float flySpawnTime)
{
	this->floatSpawnTime = floatSpawnTime;
	this->flySpawnTime = flySpawnTime;
}

void EnemyManager::SpawnEnemy(D3DXVECTOR2 pos, CEnemy::Type type)
{
	CEnemy* enemy = NULL;

	if (type == CEnemy::Type::Float)
	{
		FloatingEnemy* fEnemy;
		nowScene->obm.AddObject(fEnemy = new FloatingEnemy(pos));
		floatEnemys.push_back(fEnemy);
		enemy = fEnemy;
	}

	if (type == CEnemy::Type::Fly)
	{
		FlyingEnemy* fEnemy;
		nowScene->obm.AddObject(fEnemy = new FlyingEnemy(pos));
		flyEnemys.push_back(fEnemy);
		enemy = fEnemy;
	}

	if (type == CEnemy::Type::BigFloat)
	{
		FloatingEnemy* fEnemy;
		nowScene->obm.AddObject(fEnemy = new BigFloat(pos));
		floatEnemys.push_back(fEnemy);
		enemy = fEnemy;
	}

	if (type == CEnemy::Type::BigFly)
	{
		FlyingEnemy* fEnemy;
		nowScene->obm.AddObject(fEnemy = new BigFly(pos));
		flyEnemys.push_back(fEnemy);
		enemy = fEnemy;
	}

	allEnemys.push_back(enemy);
}

void EnemyManager::SortEnemy(CEnemy* enemy, CEnemy::Type type)
{
	auto ef = std::find(allEnemys.begin(), allEnemys.end(), enemy);

	if (ef != allEnemys.end())
		allEnemys.erase(ef);

	if (type == CEnemy::Type::Float || type == CEnemy::Type::BigFloat)
	{
		auto ef = std::find(floatEnemys.begin(), floatEnemys.end(), enemy);

		if (ef != floatEnemys.end())
			floatEnemys.erase(ef);
	}

	if (type == CEnemy::Type::Fly || type == CEnemy::Type::BigFly)
	{
		auto ef = std::find(flyEnemys.begin(), flyEnemys.end(), enemy);

		if (ef != flyEnemys.end())
			flyEnemys.erase(ef);
	}

	if (nowScene->player->target == enemy)
		nowScene->player->target = NULL;
}

void EnemyManager::SetSpawnPos(CEnemy::Type type)
{
	int index = nowScene->GetRandNum(0, 2);
	D3DXVECTOR2 spawnPos = { 0, 0 };

	if (index == 0)
		spawnPos =  + D3DXVECTOR2(-1200, nowScene->GetRandNum(200, 500));
	else if(index == 1)
		spawnPos = D3DXVECTOR2(nowScene->GetRandNum(-1000, 1000), 600);
	else if(index == 2)
		spawnPos = D3DXVECTOR2(1200, nowScene->GetRandNum(200, 500));

	auto lambda = [=] 
	{
		SpawnEnemy(Camera::GetInstance().cameraPos + spawnPos, type);
	};

	if (index == 0)
		spawnPos.x = -800;
	else if(index == 1)
		spawnPos.y = 400;
	else if(index == 2)
		spawnPos.x = 800;

	if (type == CEnemy::Type::Float)
		nowScene->obm.AddObject(new Effect(L"arrow.png", spawnPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 2, false, 1.0f, index * 90, lambda));
	else if (type == CEnemy::Type::Fly)
		nowScene->obm.AddObject(new Effect(L"arrow2.png", spawnPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 2, false, 1.0f, index * 90, lambda));
}

void EnemyManager::Spawner(float deltaTime)
{
	floatSpawnTimer += deltaTime;
	flySpawnTimer += deltaTime;

	if (floatSpawnTimer >= floatSpawnTime)
	{
		SetSpawnPos(CEnemy::Type::Float);
	
		floatSpawnTimer = 0.0f;
	}

	if (flySpawnTimer >= flySpawnTime)
	{
		SetSpawnPos(CEnemy::Type::Fly);

		flySpawnTimer = 0.0f;
	}
}
