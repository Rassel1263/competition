#pragma once
class EnemyManager
{
public:
	struct EnemyInfo
	{
		D3DXVECTOR2 pos;
		int index = 0;
	};

	int spawnIndex = 0;

	std::vector<EnemyInfo> infos;
	std::vector<CEnemy*> enemys;

public:
	void Init();

	void Spawner(D3DXVECTOR2 pos);
	void EnemySpawn(D3DXVECTOR2 pos, int index);
	void SortEnemy(CEnemy* enemy);
};

