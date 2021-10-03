#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	Scene::Init();

	SoundManager::GetInstance().Play("stage1", true);

	curStage = 1;
	nextScene = new GameScene2();

	nowScene->obm.AddObject(new Map());
	nowScene->obm.AddObject(miniMap = new MiniMap());
	nowScene->obm.AddObject(player =new Player());
	nowScene->obm.AddObject(new PlayerUI(player));
	nowScene->obm.AddObject(msgBox = new MsgBox());

	minute = gameTime / 60.0f;
	second = (int)gameTime % 60;
	millisecond = (gameTime - (int)gameTime) * 100;

	nowScene->obm.AddObject(new Font<float>(L"Number/", minute, D3DXVECTOR2(-125, 465), D3DXVECTOR2(1, 1), 30,1, 2));
	nowScene->obm.AddObject(new Font<float>(L"Number/", second, D3DXVECTOR2(-25, 465), D3DXVECTOR2(1, 1), 30, 1, 2));
	nowScene->obm.AddObject(new Font<float>(L"Number/", millisecond, D3DXVECTOR2(75, 465), D3DXVECTOR2(1, 1), 30, 1, 2));
	nowScene->obm.AddObject(new Font<float>(L"Score/", score, D3DXVECTOR2(850, 465), D3DXVECTOR2(1, 1), 35, 2, 2));

	nowScene->obm.AddObject(new StageFont(StageFont::Type::START));

	enemyManager.Init(4.0f, 7.0f);
	obstacleManager.Init(700, 1200);

	finishPos = 18000;
}

void GameScene::Update(float deltaTime)
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

		minute = gameTime / 60.0f;
		second = (int)gameTime % 60;
		millisecond = (gameTime - (int)gameTime) * 100;

		if (gameTime <= 0.0f)
		{
			stopTime = true;
			nowScene->obm.AddObject(new StageFont(StageFont::Type::FAIL));
		}
	}

	cloudTimer -= deltaTime;
	if (cloudTimer <= 0.0f)
	{
		nowScene->obm.AddObject(new Cloud());
		cloudTimer = nowScene->GetRandNum(2, 5);
	}

	if (!spawnBoss)
	{
		finishPos -= nowScene->player->dps;

		if (!player->intro)
		{
			obstacleManager.Spawner(nowScene->player->dps);
			enemyManager.Spawner(deltaTime);
		}

		if (finishPos <= 0.0f)
		{
			enemyManager.SpawnEnemy(player->pos + D3DXVECTOR2(0, 600), CEnemy::Type::BigFloat);
			finishPos = 0.0f;
		}
	}

	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}

void GameScene::UIRender()
{
	Scene::UIRender();
}
