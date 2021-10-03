#pragma once
class Item : public Object
{
public:
	Sprite spr;
	RenderInfo	ri;

	float timer = 10.0f;

	int index = 0;
	Item(D3DXVECTOR2 pos, int index);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

