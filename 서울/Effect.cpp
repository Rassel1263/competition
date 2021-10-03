#include "DXUT.h"
#include "Effect.h"

Effect::Effect(std::wstring name, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, int index, bool bCamera, float time, std::function<void()> func, int atkScene)
{
	spr.LoadAll(L"Assets/Sprites/effect/" + name);

	this->pos = pos;
	ri.scale = scale;
	ri.pivot = pivot;
	this->index = index;
	this->atkScene = atkScene;

	spr.bCamera = bCamera;

	if (index == 1)
		spr.aniMaxTime = time;
	else if (index == 2)
	{
		timer = time;
		maxTime = time;
	}

	this->func = func;
}

void Effect::Update(float deltaTime)
{
	if (index == 1)
	{
		if (atkScene > 0 && spr.scene == atkScene)
		{
			if (func && !onAttack)
			{
				SoundManager::GetInstance().Play("EnemyAttack3-2");
				onAttack = true;
				func();
			}
		}

		if (!spr.bAnimation)
		{
			if (func && !onAttack)
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
			if (func)
				func();

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
