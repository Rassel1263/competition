#include "DXUT.h"
#include "Mission.h"

Mission::Mission()
{
	spr.LoadAll(L"Assets/Sprites/Mission/mBck.png");
	spr.color.a = 0.0f;
	spr.bCamera = false;

	font.resize(3);
	fontRI.resize(3);

	for (int i = 0; i < 3; ++i)
	{
		font[i].LoadAll(L"Assets/Sprites/Mission/" + std::to_wstring(i));
		font[i].color.a = 0.0f;
		font[i].bCamera = false;

		fontRI[i].ri.pos = { 0, 200 + (float)i * -200 };
		fontRI[i].destPos = { -750, 450 + (float)i * -50 };
	}
}

void Mission::Update(float deltaTime)
{
	if (nowScene->player->intro) return;

	if (index == 0)
	{
		if (spr.color.a < 1.0f)
		{
			spr.color.a += deltaTime;
			for (auto& s : font)
				s.color.a = spr.color.a;
		}
		else
		{
			if (stopTime > 0.0f)
				stopTime -= deltaTime;
			else
			{
				stopTime = 1.0f;
				index++;
			}
		}
	}
	else if (index == 1)
	{
		if (spr.color.a > 0.0f)
			spr.color.a -= deltaTime;
		else
		{
			stopTime -= deltaTime;

			for (int i = 0; i < 3; ++i)
			{
				D3DXVec2Lerp(&fontRI[i].ri.scale, &fontRI[i].ri.scale, &D3DXVECTOR2(0.4, 0.4), 0.05f);
				D3DXVec2Lerp(&fontRI[i].ri.pos, &fontRI[i].ri.pos, &fontRI[i].destPos, 0.05f);
			}

			if (stopTime <= 0.0f)
				index++;
		}
	}
	else if (index == 2)
	{
		if (nowScene->player->ability.hp >= nowScene->player->ability.maxHp * 0.5f)
			font[0].scene = 1;
		else
			font[0].scene = 0;
	}
}

void Mission::Render()
{
	spr.Render(RenderInfo{});

	int cnt = 0;
	for (auto& spr : font)
	{
		spr.Render(fontRI[cnt].ri);
		cnt++;
	}
}

void Mission::CheckMission()
{

}

