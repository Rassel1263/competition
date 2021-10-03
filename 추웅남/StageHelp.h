#pragma once
class StageHelp : public ObjectUI
{
public:
	Sprite prevSpr;
	Sprite spr;
	Sprite complete;

	int stage = 0;

	float stopTime = 0.5f;

	int index = 0;

	StageHelp(int stage);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

