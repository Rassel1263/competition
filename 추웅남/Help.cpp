#include "DXUT.h"
#include "Help.h"

Help::Help()
{
	spr.LoadAll(L"Assets/Sprites/ui/outgame/help/help.png");
	spr.color.a = 0.0f;
}

void Help::Update(float deltaTime)
{
	if (static_cast<MainScene*>(nowScene)->input)
	{
		if (spr.color.a <= 1.0f)
			spr.color.a += deltaTime;
		else
		{
			if (Input::GetInstance().KeyDown(VK_RETURN))
				static_cast<MainScene*>(nowScene)->input = false;
		}
	}
	else
	{
		spr.color.a -= deltaTime;

		if (spr.color.a <= 0.0f)
			destroy = true;
	}
}

void Help::Render()
{
	spr.Render(RenderInfo{});
}
