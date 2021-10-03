#include "DXUT.h"
#include "Ranking.h"

Ranking::Ranking()
{
	WCHAR temp[256];
	wsprintf(temp, L"%06d", (int)nowScene->score);
	score = temp;

	int size = score.size();
	curScore.resize(size);

	for (int i = 0; i < size; ++i)
		curScore[i].LoadAll(L"Assets/Sprites/UI/Font/Score/" + score.substr(i, 1) + L".png");

	ReadFile();
}

void Ranking::Update(float deltaTime)
{
	if (initial.size() < 3)
	{
		for (char c = 'A'; c <= 'Z'; ++c)
		{
			if (Input::GetInstance().KeyDown(c))
			{
				initial.push_back(c);
				break;
			}
		}

		int size = initial.size();
		curInitial.resize(size);

		int cnt = 0;
		for (auto& spr : curInitial)
		{
			spr.LoadAll(L"Assets/Sprites/UI/Font/Rank/" + initial.substr(cnt, 1) + L".png");
			cnt++;
		}
	}
	else
		WriteFile();

	if (!initial.empty())
	{
		if (Input::GetInstance().KeyDown(VK_BACK))
			initial.pop_back();
	}
}

void Ranking::Render()
{
	int xCnt = 0;

	for (auto& spr : curScore)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-200 + xCnt * 70, 250), D3DXVECTOR2(1.5, 1.5)});
		xCnt++;
	}

	xCnt = 0;
	for (auto& spr : curInitial)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-400 + xCnt * 400, 20) });
		xCnt++;
	}

	for (int i = 0; i < 3; ++i)
	{
		xCnt = 0;
		for (auto& spr : prevInitial[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(-350 + xCnt * 100, -225 + i * -85), D3DXVECTOR2(0.4, 0.4) });
			xCnt++;
		}

		xCnt = 0;
		for (auto& spr : prevScore[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(50 + xCnt * 50, -255+ i * -85) });
			xCnt++;
		}
	}

	
}

void Ranking::ReadFile()
{
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

	prevInitial.resize(3);
	prevScore.resize(3);

	for (int i = 0; i < 3; ++i)
	{
		prevInitial[i].resize(3);
		prevScore[i].resize(6);

		for (int j = 0; j < 6; ++j)
		{
			if (j < 3)
				prevInitial[i][j].LoadAll(L"Assets/Sprites/UI/Font/Rank/" + ranks[i].initial.substr(j, 1) + L".png");

			prevScore[i][j].LoadAll(L"Assets/Sprites/UI/Font/Score/" + ranks[i].score.substr(j, 1) + L".png");
		}
	}
}

void Ranking::WriteFile()
{
	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		std::wofstream file(L"Assets/RankData.txt");

		RankInfo temp;

		temp.initial = initial;
		temp.score = score;

		ranks.push_back(temp);

		std::sort(ranks.begin(), ranks.end(), [](RankInfo& lhs, RankInfo& rhs) {return std::stoi(lhs.score) > std::stoi(rhs.score); });
		ranks.erase(ranks.end() - 1);

		for (int i = 0; i < 3; ++i)
		{
			file << ranks[i].initial << std::endl;
			file << ranks[i].score << std::endl;
		}

		auto lambda = [] {Game::GetInstance().ChangeScene(new MainScene()); };
		nowScene->obm.AddObject(new Fade(true, lambda));
	}
}
