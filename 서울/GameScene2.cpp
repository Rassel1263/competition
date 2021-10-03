#include "DXUT.h"
#include "GameScene2.h"

void GameScene2::Init()
{
	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Play("Stage2", true);

	curStage = 2;
	nextScene = new GameScene3();

	nowScene->obm.AddObject(new Map(5));

	Load();

	obm.AddObject(player = new Player());

	nowScene->obm.AddObject(new Font<float>(L"Time/", gameTime, D3DXVECTOR2(100, 500), D3DXVECTOR2(1, 1), 1, 50, 0));
	nowScene->obm.AddObject(new Font<float>(L"Score/", score, D3DXVECTOR2(900, 500), D3DXVECTOR2(1, 1), 2, 50, 0));

	for (int i = 0; i < 10; ++i)
		nowScene->obm.AddObject(new Box(D3DXVECTOR2(700 + i * 1000, nowScene->GetRandNum(-300, -50))));

	nowScene->obm.AddObject(new StageFont(StageFont::Type::START));

	enemyManager.Init();
}

void GameScene2::Update(float deltaTime)
{
	if (destScore > 0.0f)
	{
		float temp = destScore;
		destScore -= deltaTime * 1000;
		score += temp - destScore;
	}

	if (!stopTime)
	{
		gameTime -= deltaTime;

		if (gameTime <= 0.0f && !stopTime)
		{
			stopTime = true;
			obm.AddObject(new StageFont(StageFont::Type::FAIL));
		}
	}

	if (nowScene->player->pos.x >= 15000 && !spawnBoss)
		nowScene->obm.AddObject(new Boss1());

	enemyManager.Spawner(player->pos);

	Scene::Update(deltaTime);
}

void GameScene2::Render()
{
	Scene::Render();
}

void GameScene2::UIRender()
{
	Scene::UIRender();
}
