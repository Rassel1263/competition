#pragma once
class SkillEffect : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	bool fill = false;

	int index = 0;
	float time = 0.0f;
	float timer = 0.0f;

	SkillEffect(int index, float time);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

