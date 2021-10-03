#include "DXUT.h"
#include "Rank.h"

Rank::Rank()
{
	bck.LoadAll(L"Assets/Sprites/ui/outgame/rank");
	bck.color.a = 0.0f;

	std::wifstream file(L"Assets/RankData.txt");

	ranks.resize(3);

	if (file.is_open())
	{
		for (int i = 0; i < 3; ++i)
		{
			file >> ranks[i].initial;
			file >> ranks[i].score;
		}
	}

	initial.resize(3);
	score.resize(3);

	for (int i = 0; i < 3; ++i)
	{
		initial[i].resize(3);
		score[i].resize(6);

		for (int j = 0; j < 6; ++j)
		{
			if (j < 3)
			{
				initial[i][j].LoadAll(L"Assets/Sprites/ui/Font/apb/" + ranks[i].initial.substr(j, 1) + L".png");
				initial[i][j].color.a = 0.0f;
			}

			score[i][j].LoadAll(L"Assets/Sprites/ui/Font/Number/" + ranks[i].score.substr(j, 1) + L".png");
			score[i][j].color.a = 0.0f;
		}
	}
}

void Rank::Update(float deltaTime)
{
	if (static_cast<MainScene*>(nowScene)->input)
	{
		if(bck.color.a <= 1.0f)
			bck.color.a += deltaTime;
		else
		{
			if (Input::GetInstance().KeyDown(VK_RETURN))
				static_cast<MainScene*>(nowScene)->input = false;
		}
	}
	else
	{
		bck.color.a -= deltaTime;

		if (bck.color.a <= 0.0f)
			destroy = true;
	}
}

void Rank::Render()
{
	bck.Render(RenderInfo{});

	int cnt = 0;
	for (int i = 0; i < 3; ++i)
	{
		cnt = 0;
		for (auto& spr : initial[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(-230 + cnt * 100, 150 - i * 200) });
			spr.color.a = bck.color.a;
			cnt++;
		}

		cnt = 0;
		for (auto& spr : score[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(370 + cnt * 70, 150- i * 200), D3DXVECTOR2(2, 2) });
			spr.color.a = bck.color.a;
			cnt++;
		}
	}
}
