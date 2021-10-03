#pragma once
class CalcPage : public ObjectUI
{
public:
	int index = 0;

	Sprite bck;
	RenderInfo ri;

	Sprite fontSpr;
	Sprite skillSpr;

	std::vector<Sprite> skills;
	std::vector<int> skillNums;

	float hp = 0.0f;
	float maxCombo = 0.0f;

	bool drawFont = false;

	float stopTimer = 1.0f;
	D3DXCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	CalcPage();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	void Calc(float& num, float deltaTime);
};

