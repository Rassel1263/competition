#pragma once
class EnemyManager
{
public:
	std::vector<CEnemy*> allEnemys;
	std::vector<FloatingEnemy*> floatEnemys;
	std::vector<FlyingEnemy*> flyEnemys;

public:
	float floatSpawnTime = 0.0f;
	float floatSpawnTimer = 0.0f;

	float flySpawnTime = 0.0f;
	float flySpawnTimer = 0.0f;

	void Init(float floatSpawnTime, float flySpawnTime);
	void SpawnEnemy(D3DXVECTOR2 pos, CEnemy::Type type);
	void SortEnemy(CEnemy* enemy, CEnemy::Type type);
	void SetSpawnPos(CEnemy::Type type);
	void Spawner(float deltaTime);
};

