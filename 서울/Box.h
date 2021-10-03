#pragma once
class Box : public Object
{
public:
	Sprite spr;
	RenderInfo ri;
	bool hit = false;

	Box(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

