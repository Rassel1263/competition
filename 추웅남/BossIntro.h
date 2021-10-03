#pragma once
class BossIntro : public ObjectUI
{
public:
	Sprite spr;

	int blink = 0;
	float destColor = 1.0f;

	BossIntro();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

