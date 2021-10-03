#include "DXUT.h"
#include "SkillEffect.h"

SkillEffect::SkillEffect(int index, float time)
{
	if (index == 1 || index == 3)
	{
		spr.LoadAll(L"Assets/Sprites/effect/Player/skill.png");
		layer = -5;
	}
	else if (index == 2)
	{
		spr.LoadAll(L"Assets/Sprites/effect/Player/skill2.png");
		layer = 1100;
	}

	spr.color.a = 0.0f;
	spr.bCamera = false;

	this->time = time;
	this->timer = time;

}

void SkillEffect::Update(float deltaTime)
{
	if (index != 3)
	{
		if (!fill)
		{
			spr.color.a += deltaTime * 2;

			if (spr.color.a >= 1.0f)
				fill = true;
		}
		else
		{
			if (timer <= 0.0f)
			{
				spr.color.a -= deltaTime * 2;

				if (spr.color.a <= 0.0f)
					destroy = true;

			}
		}
	}
	else
	{
		if (nowScene->player->nuclear)
			spr.color.a += deltaTime * 2;
		else
		{
			spr.color.a -= deltaTime * 2;

			if (spr.color.a <= 0.0f)
				destroy = true;
		}
	}

	timer -= deltaTime;
	spr.color.a = std::clamp(spr.color.a, 0.0f, 1.0f);
}

void SkillEffect::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
