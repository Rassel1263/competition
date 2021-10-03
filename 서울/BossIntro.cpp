#include "DXUT.h"
#include "BossIntro.h"

BossIntro::BossIntro()
{
	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Play("BossIntro");

	spr.LoadAll(L"Assets/Sprites/effect/enemy/bossIntro.png");
	spr.color.a = 0.0f;
	spr.bCamera = false;

	Camera::GetInstance().destCameraPos.x = 16000;

	nowScene->player->stop = true;
	nowScene->player->fallowCamera = false;
	nowScene->stopTime = true;
}

void BossIntro::Update(float deltaTime)
{
	spr.color.a += deltaTime * destColor * 2;

	if (spr.color.a <= 0.0f || spr.color.a >= 1.0f)
	{
		destColor = -destColor;
		blink++;
		spr.color.a = std::clamp(spr.color.a, 0.0f, 1.0f);
	}

	if (spr.color.a <= 0.0f && blink >= 4)
	{
		nowScene->player->stop = false;
		nowScene->player->fallowCamera = true;
		nowScene->stopTime = false;
		SoundManager::GetInstance().Play("BossField", true);
		destroy = true;
	}
}

void BossIntro::Render()
{
	spr.Render(RenderInfo{});
}
