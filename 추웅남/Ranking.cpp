#include "DXUT.h"
#include "Ranking.h"

Ranking::Ranking()
{
	WCHAR temp[256];
	wsprintf(temp, L"%06d", (int)nowScene->score);
	score = temp;

	curScore.resize(score.size());

	int cnt = 0;
	for (auto& spr : curScore)
	{
		spr.LoadAll(L"Assets/Sprites/ui/Font/Number/" + score.substr(cnt, 1) + L".png");
		cnt++;
	}

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
		for (int i = 0; i < size; ++i)
			curInitial[i].LoadAll(L"Assets/Sprites/ui/Font/apb/" + initial.substr(i, 1) + L".png");
	}
	else
		WriteFile();

	if(!initial.empty())
	{
		if (Input::GetInstance().KeyDown(VK_BACK))
			initial.pop_back();
	}
}

void Ranking::Render()
{
	int cnt = 0;

	for (auto& spr : curScore)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-100 + cnt * 30, 400) });
		cnt++;
	}

	cnt = 0;
	for (auto& spr : curInitial)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-600 + cnt * 600, 20), D3DXVECTOR2(2, 2) });
		cnt++;
	}

	for (int i = 0; i < 3; ++i)
	{
		cnt = 0;
		for (auto& spr : prevInitial[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(-300 + cnt * 70, -200 + -i * 100) });
			cnt++;
		}

		cnt = 0;
		for (auto& spr : prevScore[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(100 + cnt * 50, -200 + -i * 100), D3DXVECTOR2(1.5, 1.5)});
			cnt++;
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
			if(j < 3)
				prevInitial[i][j].LoadAll(L"Assets/Sprites/ui/Font/apb/" + ranks[i].initial.substr(j, 1) + L".png");

			prevScore[i][j].LoadAll(L"Assets/Sprites/ui/Font/Number/" + ranks[i].score.substr(j, 1) + L".png");
		}
	}
}

void Ranking::WriteFile()
{
	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		RankInfo temp;

		temp.initial = initial;
		temp.score = score;

		ranks.push_back(temp);

		std::sort(ranks.begin(), ranks.end(), [](RankInfo& lhs, RankInfo& rhs) {return std::stoi(lhs.score) > std::stoi(rhs.score); });

		ranks.erase(ranks.end() - 1);

		std::wofstream file(L"Assets/RankData.txt");

		if (file.is_open())
		{
			for (int i = 0; i < 3; ++i)
			{
				file << ranks[i].initial << std::endl;
				file << ranks[i].score << std::endl;
			}
		}

		Game::GetInstance().ChangeScene(new MainScene());
	}
}
