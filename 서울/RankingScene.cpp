#include "DXUT.h"
#include "RankingScene.h"

void RankingScene::Init()
{
	Scene::Load();

	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Play("Ranking", true);

	nowScene->obm.AddObject(new Ranking());
}

void RankingScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void RankingScene::Render()
{
	Scene::Render();
}

void RankingScene::UIRender()
{
	Scene::UIRender();
}
