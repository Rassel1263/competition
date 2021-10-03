#pragma once
class Airsupport : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	bool onAttack = false;

	Airsupport();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

