#include "DXUT.h"
#include "Scene.h"

float Scene::score = 0.0f;

void Scene::Init()
{
}

void Scene::Update(float deltaTime)
{

	if (curStage > 0)
	{
		if (Input::GetInstance().KeyDown(VK_F1))
			player->invincible = !player->invincible;

		if (Input::GetInstance().KeyDown(VK_F2))
			player->PlusMp(player->maxMp);

		if (Input::GetInstance().KeyDown(VK_F3))
		{
			for (auto& enemy : enemyManager.enemys)
			{
				if (enemy->pos.x < Camera::GetInstance().cameraPos.x + 960 && enemy->pos.x > Camera::GetInstance().cameraPos.x - 960&&
					enemy->pos.y < Camera::GetInstance().cameraPos.y + 540 && enemy->pos.y > Camera::GetInstance().cameraPos.y - 540)
				{
					enemy->Hit(enemy->ability.maxHp, D3DXVECTOR2(0, 0));
				}
			}
		}
	}

	if (Input::GetInstance().KeyDown(VK_F4))
		Game::GetInstance().ChangeScene(new MainScene());

	if (Input::GetInstance().KeyDown(VK_F5))
		Game::GetInstance().ChangeScene(new GameScene());

	if (Input::GetInstance().KeyDown(VK_F6))
		Game::GetInstance().ChangeScene(new GameScene2());

	if (Input::GetInstance().KeyDown(VK_F7))
		Game::GetInstance().ChangeScene(new GameScene3());

	if (Input::GetInstance().KeyDown(VK_F11))
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

void Scene::AddScore(int value)
{
	this->destScore += value;
}

void Scene::Load()
{
	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/ColorShader.fx", 1);
	ShaderManager::GetInstance().CreateEffect("Outline", L"Assets/Shader/OutlineShader.fx", 1);

	// 플레이어

	std::wstring path = L"Assets/Sound/Player/Attack/";

	SoundManager::GetInstance().Create("Basic", path + L"Basic.mp3", 5);
	SoundManager::GetInstance().Create("Airshot", path + L"Airshot.mp3", 1);
	SoundManager::GetInstance().Create("Grenade", path + L"Grenade.mp3", 1);
	SoundManager::GetInstance().Create("Kick", path + L"Kick.mp3", 1);
	SoundManager::GetInstance().Create("Machine", path + L"Machine.mp3", 10);
	SoundManager::GetInstance().Create("NuclearBoom", path + L"NuclearBoom.mp3", 1);
	SoundManager::GetInstance().Create("NuclearFall", path + L"NuclearFall.mp3", 1);
	SoundManager::GetInstance().Create("NuclearReady", path + L"NuclearReady.mp3", 1);
	SoundManager::GetInstance().Create("NuclearReady2", path + L"NuclearReady2.mp3", 1);
	SoundManager::GetInstance().Create("NuclearSound", path + L"NuclearSound.mp3", 1);
	SoundManager::GetInstance().Create("Slide", path + L"Slide.mp3", 1);
	SoundManager::GetInstance().Create("Sniper", path + L"Sniper.mp3", 1);
	SoundManager::GetInstance().Create("SniperReady", path + L"SniperReady.mp3", 1);

	// 보이스
	path = L"Assets/Sound/Player/Voice/";
	SoundManager::GetInstance().Create("AirShootVoi", path + L"AirShoot.mp3", 1);
	SoundManager::GetInstance().Create("DieVoi", path + L"Die.mp3", 1);
	SoundManager::GetInstance().Create("GrenadeVoi", path + L"Grenade.mp3", 1);
	SoundManager::GetInstance().Create("GunKataVoi", path + L"GunKata.mp3", 1);
	SoundManager::GetInstance().Create("Hit1", path + L"Hit1.mp3", 1);
	SoundManager::GetInstance().Create("Hit2", path + L"Hit2.mp3", 1);
	SoundManager::GetInstance().Create("Hit3", path + L"Hit3.mp3", 1);
	SoundManager::GetInstance().Create("JumpVoi", path + L"Jump.mp3", 1);
	SoundManager::GetInstance().Create("MachineVoi", path + L"Machine.mp3", 1);
	SoundManager::GetInstance().Create("MoveShotVoi", path + L"MoveShot.mp3", 1);
	SoundManager::GetInstance().Create("NuclearVoi", path + L"Nuclear.mp3", 1);
	SoundManager::GetInstance().Create("SlideVoi", path + L"Slide.mp3", 1);
	SoundManager::GetInstance().Create("SniperVoi", path + L"Sniper.mp3", 1);

	// 적
	path = L"Assets/Sound/Enemy/";
	SoundManager::GetInstance().Create("EnemyHit", path + L"Hit.mp3", 1);
	SoundManager::GetInstance().Create("EnemySpawn1", path + L"Spawn/1.mp3", 1);
	SoundManager::GetInstance().SetVolume("EnemySpawn1", L"left", 100);
	SoundManager::GetInstance().SetVolume("EnemySpawn1", L"right", 1000);

	SoundManager::GetInstance().Create("EnemySpawn2", path + L"Spawn/2.mp3", 1);
	SoundManager::GetInstance().SetVolume("EnemySpawn2", L"left", 100);
	SoundManager::GetInstance().SetVolume("EnemySpawn2", L"right", 700);

	SoundManager::GetInstance().Create("EnemySpawn3", path + L"Spawn/3.mp3", 1);
	SoundManager::GetInstance().SetVolume("EnemySpawn3", L"left", 100);
	SoundManager::GetInstance().SetVolume("EnemySpawn3", L"right", 700);

	SoundManager::GetInstance().Create("EnemySpawn4", path + L"Spawn/4.mp3", 1);
	SoundManager::GetInstance().SetVolume("EnemySpawn4", L"left", 100);
	SoundManager::GetInstance().SetVolume("EnemySpawn4", L"right", 700);

	SoundManager::GetInstance().Create("EnemyAttack1", path + L"Attack/1.mp3", 1);
	SoundManager::GetInstance().Create("EnemyAttack2", path + L"Attack/2.mp3", 1);
	SoundManager::GetInstance().Create("EnemyAttack3", path + L"Attack/3.mp3", 1);
	SoundManager::GetInstance().Create("EnemyAttack3-2", path + L"Attack/3-2.mp3", 1);

	
	// 이펙트
	path = L"Assets/Sound/Effect/";
	SoundManager::GetInstance().Create("Box", path + L"Box.mp3", 1);
	SoundManager::GetInstance().Create("Fight", path + L"Fight.mp3", 1);
	SoundManager::GetInstance().Create("Heal", path + L"Heal.mp3", 1);
	SoundManager::GetInstance().Create("Hit", path + L"Hit.mp3", 1);
	SoundManager::GetInstance().Create("Item", path + L"Item.mp3", 1);
	SoundManager::GetInstance().Create("Result", path + L"Result.mp3", 1);
	SoundManager::GetInstance().Create("Walk", path + L"Walk.mp3", 1);

	// BGM
	path = L"Assets/Sound/BGM/";
	SoundManager::GetInstance().Create("BossField", path + L"BossField.mp3", 1);
	SoundManager::GetInstance().Create("BossIntro", path + L"BossIntro.mp3", 1);
	//SoundManager::GetInstance().Create("Main", path + L"Main.mp3", 1);
	SoundManager::GetInstance().Create("Main", L"Assets/Sound/BGM/Main.mp3", 1);
	SoundManager::GetInstance().Create("Ranking", path + L"Ranking.mp3", 1);
	SoundManager::GetInstance().Create("Stage1", path + L"stage1.mp3", 1);
	SoundManager::GetInstance().Create("Stage2", path + L"Stage2.mp3", 1);
	SoundManager::GetInstance().Create("Stage3", path + L"Stage3.mp3", 1);

	// UI
	path = L"Assets/Sound/UI/";
	SoundManager::GetInstance().Create("ClickBtn", path + L"ClickBtn.mp3", 1);
	SoundManager::GetInstance().Create("MoveBtn", path + L"MoveBtn.mp3", 1);
}
