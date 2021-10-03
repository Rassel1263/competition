#include "DXUT.h"
#include "RankingScene.h"

void RankingScene::Init()
{
	obm.AddObject(new Ranking());
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
