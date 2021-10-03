#pragma once
class Spectrum : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	ColorShader * colorShader = NULL;

	bool onAttack = false;
	int index = 0;

	float attackTime = 0.0f;
	float attackTimer = 0.0f;

	Spectrum(int index, Sprite spr, RenderInfo ri, int layer, float attackTime, float attackTimer);

	virtual void Update(float deltaTime) override;
	virtual void Render();
};

