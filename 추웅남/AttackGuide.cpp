#include "DXUT.h"
#include "AttackGuide.h"

AttackGuide::AttackGuide(D3DXVECTOR2 pos, D3DXVECTOR2 scale, int index, float time, std::function<void()> func)
{
	this->pos = pos;
	ri.scale = scale;
	this->index = index;
	this->timer = time;
	this->maxTime = time;
	this->func = func;

	if (index == 1)
	{
		bck.LoadAll(L"Assets/Sprites/effect/attackGuide.png");
		bckRI.scale = scale;

		spr.LoadAll(L"Assets/Sprites/effect/attackGuide.png");
		ri.scale = { 0 ,0 };
	}
	else if (index == 2)
	{
		bck.LoadAll(L"Assets/Sprites/effect/attackGuide2.png");
		bckRI.scale = scale;

		spr.LoadAll(L"Assets/Sprites/effect/attackGuide2.png");
		ri.scale = { 1 ,0 };
	}
}

void AttackGuide::Update(float deltaTime)
{
	timer -= deltaTime;

	if (index == 1)
		ri.scale = bckRI.scale * (1 - timer / maxTime);
	else if (index == 2)
		ri.scale.y = bckRI.scale.y * (1 - timer / maxTime);

	if (timer <= 0.0f)
	{
		if (func) func();
		destroy = true;
	}

}

void AttackGuide::Render()
{
	ri.pos = bckRI.pos = pos;

	bck.Render(bckRI);
	spr.Render(ri);
}
