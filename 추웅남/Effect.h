#pragma once
class Effect : public Object
{
public:
	std::function<void()> func;

	int index = 0;

	Sprite spr;
	RenderInfo ri;

	float timer = 0.0f;
	float maxTime = 0.0f;

	Effect(std::wstring name, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, int index, bool bCamera, float timer, float rotate = 0.0f, std::function<void()> func = NULL);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

};

