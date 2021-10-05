#include "DXUT.h"
#include "Scene.h"

float Scene::score = 0.0f;

void Scene::Init()
{
	ShaderManager::GetInstance().Create("Color", L"Assets/Shader/ColorShader.fx", 1);

	std::wstring path = L"Assets/Sound/Player/";

	SoundManager::GetInstance().StopAll();

	// 플레이어
	SoundManager::GetInstance().Create("airBoom", path + L"airBoom.mp3", 1);
	SoundManager::GetInstance().Create("airMove", path + L"airMove.mp3", 1, 400);
	SoundManager::GetInstance().Create("airStart", path + L"airStart.mp3", 1, 600);
	SoundManager::GetInstance().Create("Machine", path + L"Machine.mp3", 5);
	SoundManager::GetInstance().Create("Missile", path + L"Missile.mp3", 3);
	SoundManager::GetInstance().Create("Navalgun", path + L"Navalgun.mp3", 3, 400);
	SoundManager::GetInstance().Create("NavalHit", path + L"NavalHit.mp3", 3, 250);

	// 적
	path = L"Assets/Sound/Enemy/";
	SoundManager::GetInstance().Create("Explo", path + L"Explo.mp3", 5);
	SoundManager::GetInstance().Create("BossIntro", path + L"BossIntro.mp3", 1);

	// 이펙트
	path = L"Assets/Sound/Effect/";
	SoundManager::GetInstance().Create("Item", path + L"Item.mp3", 1);
	SoundManager::GetInstance().Create("msg1", path + L"msg.mp3", 1);
	SoundManager::GetInstance().Create("msg2", path + L"msg2.mp3", 1);
	SoundManager::GetInstance().Create("msg3", path + L"msg3.mp3", 1);
	SoundManager::GetInstance().Create("reload", path + L"reload.mp3", 1);
	SoundManager::GetInstance().Create("skillMsg", path + L"skillMsg.mp3", 1);
	SoundManager::GetInstance().Create("start", path + L"start.mp3", 1);

	// 버튼
	path = L"Assets/Sound/Btn/";
	SoundManager::GetInstance().Create("ClickBtn", path + L"ClickBtn.mp3", 1);
	SoundManager::GetInstance().Create("MoveBtn", path + L"MoveBtn.mp3", 1);

	// bgm
	path = L"Assets/Sound/BGM/";
	SoundManager::GetInstance().Create("boss", path + L"boss.mp3", 1, 300);
	SoundManager::GetInstance().Create("main", path + L"main.mp3", 1, 300);
	SoundManager::GetInstance().Create("stage1", path + L"stage1.mp3", 1, 300);
	SoundManager::GetInstance().Create("stage2", path + L"stage2.mp3", 1, 300);
	SoundManager::GetInstance().Create("win", path + L"win.mp3", 1, 300);
}

void Scene::Update(float deltaTime)
{
	if (curStage > 0)
	{
		if (Input::GetInstance().KeyDown(VK_F1))
			player->god = !player->god;

		if (Input::GetInstance().KeyDown(VK_F3))
			stopTime = !stopTime;
	}

	if (Input::GetInstance().KeyDown(VK_F4))
		Game::GetInstance().ChangeScene(new MainScene());

	if (Input::GetInstance().KeyDown(VK_F5))
		Game::GetInstance().ChangeScene(new GameScene());

	if (Input::GetInstance().KeyDown(VK_F6))
		Game::GetInstance().ChangeScene(new GameScene2());

	if (Input::GetInstance().KeyDown(VK_F10))
		Game::GetInstance().ChangeScene(new RankingScene());

	obm.Collision();
	obm.Update(deltaTime);
}

void Scene::Render()
{
	obm.Render();
}

void Scene::UIRender()
{
	obm.UIRender();
}

int Scene::GetRandNum(int min, int max)
{
	std::default_random_engine rnd(rd());
	std::uniform_int_distribution<int> dis(min, max);

	return dis(rnd);
}

D3DXVECTOR2 Scene::GetRandVec(int minX, int maxX, int minY, int maxY)
{
	std::default_random_engine rnd(rd());
	std::uniform_int_distribution<int> x(minX, maxX);
	std::uniform_int_distribution<int> y(minY, maxY);

	return D3DXVECTOR2(x(rnd), y(rnd));
}

float Scene::GetAngleFromTarget(D3DXVECTOR2 pos, D3DXVECTOR2 targetPos)
{
	D3DXVECTOR2 distance = targetPos - pos;

	return D3DXToDegree(atan2(distance.y, distance.x));
}
