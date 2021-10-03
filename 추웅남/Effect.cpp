#include "DXUT.h"
#include "Effect.h"

Effect::Effect(std::wstring name, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, int index, bool bCamera, float timer, float rotate, std::function<void()> func)
{
	spr.LoadAll(L"Assets/Sprites/effect/" + name);

	if (index == 1)
		spr.aniMaxTime = timer;
	else if (index == 2)
	{
		this->timer = timer;
		this->maxTime = timer;
	}

	this->pos = pos;
	this->ri.scale = scale;
	ri.pivot = pivot;
	this->index = index;

	spr.bCamera = bCamera;
	ri.rotate = rotate;
	this->func = func;

	layer = 10;
}

void Effect::Update(float deltaTime)
{
	if (index == 1)
	{
		if (!spr.bAnimation)
		{
			if (func)
				func();

			destroy = true;
		}
	}
	else if (index == 2)
	{
		timer -= deltaTime;

		spr.color.a = timer / maxTime;

		if (spr.color.a <= 0.0f)
		{
			if (func) func();
			destroy = true;
		}
	}

	spr.Update(deltaTime);
}

void Effect::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
