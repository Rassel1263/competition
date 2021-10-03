#pragma once
class Rank : public Object
{
public:
	Sprite bck;
	Sprite spr;

	std::vector<std::vector<Sprite>> initial;
	std::vector<std::vector<Sprite>> score;

	std::vector<RankInfo> ranks;

	Rank();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

