#pragma once
class UIEffect : public ObjectUI
{
public:
	Sprite spr;
	RenderInfo ri;
	UIEffect(Sprite spr, D3DXVECTOR2 pos, float visibleTime, int layer);

	float maxTime = 0.0f;
	float timer = 0.0f;

	virtual void Update(float deltaTime);
	virtual void Render();
};

