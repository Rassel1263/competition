#pragma once
class HitEffect : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	HitEffect();

	virtual void Update(float deltaTime) override;
	virtual void Render();
};

