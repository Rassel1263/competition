#include "DXUT.h"
#include "FocusSKill.h"

FocusSKill::FocusSKill()
{
	bck.LoadAll(L"Assets/Sprites/effect/focus/1.png");
	bck.color.a = 0.0f;
	bck.bCamera = false;

	gauge.LoadAll(L"Assets/Sprites/effect/focus/g.png");
	gauge.color.a = 0.0f;
	gauge.bCamera = false;
}

void FocusSKill::Update(float deltaTime)
{
	if (nowScene->player->skill1)
	{
		if(bck.color.a <= 0.5f)
			bck.color.a += deltaTime;

		gauge.heightRatio = 1 - nowScene->player->skill1Timer / 4.0f;
	 }
	else
	{
		bck.color.a -= deltaTime;
		if (bck.color.a <= 0.0f)
			destroy = true;
	}

	gauge.color = bck.color;
}

void FocusSKill::Render()
{
	bck.Render(RenderInfo{});
	gauge.Render(RenderInfo{D3DXVECTOR2(-400, 0)});
}
