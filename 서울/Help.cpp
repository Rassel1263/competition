#include "DXUT.h"
#include "Help.h"

Help::Help()
{
	bck.LoadAll(L"Assets/Sprites/effect/bck.png");
	bck.color.a = 0.0f;

	spr.LoadAll(L"Assets/Sprites/UI/main/help");
	spr.color.a = 0.0f;
}

void Help::Update(float deltaTime)
{
	if (static_cast<MainScene*>(nowScene)->input)
	{
		if(spr.color.a < 1.0f)
			spr.color.a += deltaTime;

		if (Input::GetInstance().KeyDown(VK_RETURN))
		{
			static_cast<MainScene*>(nowScene)->input = false;
		}
	}
	else
	{
		spr.color.a -= deltaTime;

		if (spr.color.a <= 0.0f)
			destroy = true;
	}

	bck.color.a = spr.color.a;
	bck.color.a = std::clamp(bck.color.a, 0.0f, 0.7f);
}

void Help::Render()
{
	bck.Render(RenderInfo{});
	spr.Render(RenderInfo{});
}
