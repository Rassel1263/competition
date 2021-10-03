#include "DXUT.h"
#include "MainScene.h"

void MainScene::Init()
{
	Scene::Load();

	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Play("Main", true);

	EnhanceData::GetInstance().Init();

	Camera::GetInstance().cameraPos = { 0, 0 };
	Camera::GetInstance().destCameraPos = { 0, 0 };


	if (TextureManager::GetInstance().threadCnt <= 0)
		nowScene->obm.AddObject(new LoadSprite());
	else
		nowScene->obm.AddObject(new Main());
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
