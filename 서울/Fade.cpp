#include "DXUT.h"
#include "Fade.h"

Fade::Fade(bool fill, std::function<void()> func)
{
	spr.LoadAll(L"Assets/Sprites/effect/bck.png");
	
	(fill) ? spr.color.a = 0.0f : spr.color.a = 1.0f;
	this->func = func;

	spr.bCamera = false;
	this->fill = fill;

	layer = 10;
}

void Fade::Update(float deltaTime)
{
	if (fill)
	{
		spr.color.a += deltaTime;

		if (spr.color.a >= 1.0f)
		{
			if (func)
				func();
		}
	}
	else
	{
		spr.color.a -= deltaTime;

		if (spr.color.a <= 0.0f)
			destroy = true;
	}
}

void Fade::Render()
{
	spr.Render(RenderInfo{});
}
