#pragma once
class AfterImage : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	ColorShader* colorShader = NULL;

	float timer = 0.0f;
	float maxTime = 0.0f;

	D3DXVECTOR2* fallowPos = NULL;

	int index = 0;
	AfterImage(Sprite spr, RenderInfo ri, D3DXCOLOR color, float time, int layer);
	AfterImage(int scene, Sprite spr, RenderInfo ri, D3DXVECTOR2* fallowPos, int layer);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

