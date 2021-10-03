#include "DXUT.h"
#include "Fade.h"

Fade::Fade(bool fill, std::function<void()> func)
{
	this->fill = fill;
	this->func = func;

	spr.LoadAll(L"Assets/Sprites/black.png");
	spr.bCamera = false;

	if (fill)
		spr.color.a = 0.0f;

	layer = 20;
}

void Fade::Update(float deltaTime)
{
	if (fill)
	{
		if (spr.color.a <= 1.0f)
			spr.color.a += deltaTime;
		else
		{
			if (func)
				func();
		}
	}
	else
	{
		if (spr.color.a > 0.0f)
			spr.color.a -= deltaTime;
		else
		{
			if (func)
				func();

			destroy = true;
		}
	}
}

void Fade::Render()
{
	spr.Render(RenderInfo{});
}
