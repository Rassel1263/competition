#include "DXUT.h"
#include "EnemyManager.h"

void EnemyManager::Init()
{
	std::wifstream file(L"Assets/EnemyData/" + std::to_wstring(nowScene->curStage) + L".txt");

	if (file.is_open())
	{
		while (!file.eof())
		{
			EnemyInfo temp;

			file >> temp.pos.x;
			file >> temp.pos.y;
			file >> temp.index;

			infos.push_back(temp);
		}
	}
}

void EnemyManager::Spawner(D3DXVECTOR2 pos)
{
	if (spawnIndex < infos.size())
	{
		if (infos[spawnIndex].pos.x - pos.x <= 1000)
		{
			EnemySpawn(infos[spawnIndex].pos, infos[spawnIndex].index);
			++spawnIndex;
		}
	}
}

void EnemyManager::EnemySpawn(D3DXVECTOR2 pos, int index)
{
	CEnemy* enemy;

	if (index == 1)
		nowScene->obm.AddObject(enemy = new Enemy1(pos));
	else if (index == 2)
		nowScene->obm.AddObject(enemy = new Enemy2(pos));
	else if (index == 3)
		nowScene->obm.AddObject(enemy = new Enemy3(pos));
	else if (index == 4)
		nowScene->obm.AddObject(enemy = new Enemy4(pos));

	SoundManager::GetInstance().Play("EnemySpawn" + std::to_string(index));

	enemys.push_back(enemy);
}

void EnemyManager::SortEnemy(CEnemy * enemy)
{
	auto ef = std::find(enemys.begin(), enemys.end(), enemy);

	if (ef != enemys.end())
		enemys.erase(ef);
}
