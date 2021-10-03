#pragma once
class CalcPage : public ObjectUI
{
public:
	Sprite bck;

	float stopTime = 1.0f;

	D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	float hp = 0.0f;
	float kill = 0.0f;

	int index = 0;

	CalcPage();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void Calc(float& num, float deltaTime);

};

