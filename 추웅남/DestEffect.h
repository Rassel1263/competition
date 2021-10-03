#pragma once
class DestEffect : public ObjectUI
{
public:
	Sprite spr;
	RenderInfo ri;

	DestEffect(D3DXVECTOR2 pos, Sprite spr);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

