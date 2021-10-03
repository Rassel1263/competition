#pragma once
class Nuclear : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	bool onAttack = false;

	Nuclear(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

