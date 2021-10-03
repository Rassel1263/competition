#include "DXUT.h"
#include "Rank.h"

Rank::Rank()
{
	std::wifstream file(L"Assets/RankData.txt");

	ranks.resize(3);

	if (file.is_open())
	{
		for(int i = 0; i < 3; ++i)
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
				initial[i][j].LoadAll(L"Assets/Sprites/UI/Font/Rank/" + ranks[i].initial.substr(j, 1) + L".png");
				initial[i][j].color.a = 0.0f;
			}

			score[i][j].LoadAll(L"Assets/Sprites/UI/Font/Score/" + ranks[i].score.substr(j, 1) + L".png");
			score[i][j].color.a = 0.0f;
		}
	}
	bck.LoadAll(L"Assets/Sprites/effect/bck.png");
	bck.color.a = 0.0f;

	spr.LoadAll(L"Assets/Sprites/UI/main/rank");
	spr.color.a = 0.0f;
}

void Rank::Update(float deltaTime)
{

	if (static_cast<MainScene*>(nowScene)->input)
	{
		if (spr.color.a < 1.0f)
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

void Rank::Render()
{
	bck.Render(RenderInfo{});
	spr.Render(RenderInfo{});

	int xCnt = 0;
	for (int i = 0; i < 3; ++i)
	{
		xCnt = 0;
		for (auto& s : initial[i])
		{
			s.Render(RenderInfo{ D3DXVECTOR2(-500 + xCnt * 150, 100 + i * -150), D3DXVECTOR2(0.8, 0.8) });
			s.color.a = spr.color.a;
			xCnt++;
		}

		xCnt = 0;
		for (auto& s : score[i])
		{
			s.Render(RenderInfo{ D3DXVECTOR2(100 + xCnt * 100, 100 + i * -150), D3DXVECTOR2(2, 2)});
			s.color.a = spr.color.a;
			xCnt++;
		}
	}
}
