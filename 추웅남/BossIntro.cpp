#include "DXUT.h"
#include "BossIntro.h"

BossIntro::BossIntro()
{
	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Play("BossIntro");

	spr.LoadAll(L"Assets/Sprites/effect/warning.png");
	spr.color.a = 0.0f;
	spr.bCamera = false;
}

void BossIntro::Update(float deltaTime)
{
	spr.color.a += deltaTime * destColor * 1.5f;

	if (spr.color.a <= 0.0f || spr.color.a >= 1.0f)
	{
		destColor = -destColor;
		spr.color.a = std::clamp(spr.color.a, 0.0f, 1.0f);
		blink++;
	}

	if (spr.color.a <= 0.0f && blink >= 4)
	{
		SoundManager::GetInstance().Play("boss", true);
		destroy = true;
	}
}

void BossIntro::Render()
{
	spr.Render(RenderInfo{});
}
