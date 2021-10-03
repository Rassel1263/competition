#include "DXUT.h"
#include "MainScene.h"

void MainScene::Init()
{
	score = 0.0f;
	destScore = 0.0f;

	Scene::Init();

	SoundManager::GetInstance().Play("main", true);

	if (TextureManager::GetInstance().threadCnt <= 0)
		obm.AddObject(new LoadSprite());
	else
		obm.AddObject(new Main());
}

void MainScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void MainScene::Render()
{
	Scene::Render();
}

void MainScene::UIRender()
{
	Scene::UIRender();
}
