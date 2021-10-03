#pragma once
class Cloud : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	float speed = 0.0f;

	Cloud();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

