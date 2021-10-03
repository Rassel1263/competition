#pragma once
class Effect : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	int index = 0;
	float timer = 0.0f;
	float maxTime = 0.0f;
	int atkScene = 0;

	bool onAttack = false;

	std::function<void()> func;

	Effect(std::wstring name, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, int index, bool bCamera, float time, std::function<void()> func = NULL, int atkScene = 0);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

