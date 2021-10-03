#pragma once

struct RankInfo
{
	std::wstring initial = L"";
	std::wstring score = L"";
};

class Ranking : public Object
{
public:
	std::vector<std::vector<Sprite>> prevInitial;
	std::vector<std::vector<Sprite>> prevScore;

	std::wstring initial = L"";
	std::wstring score = L"";

	std::vector<Sprite> curInitial;
	std::vector<Sprite> curScore;

	std::vector<RankInfo> ranks;

	Ranking();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void ReadFile();
	void WriteFile();
};

