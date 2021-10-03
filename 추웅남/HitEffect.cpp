#include "DXUT.h"
#include "HitEffect.h"

HitEffect::HitEffect()
{
	spr.LoadAll(L"Assets/Sprites/effect/ouch.png");
	spr.bCamera = false;
}

void HitEffect::Update(float deltaTime)
{
	spr.color.a -= deltaTime;

	if (spr.color.a <= 0.0f)
		destroy = true;
}

void HitEffect::Render()
{
	spr.Render(RenderInfo{});
}
