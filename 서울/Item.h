#pragma once
class Item : public Object
{
public:
	int index = 0;

	Sprite spr;
	RenderInfo ri;

	Item(int index, D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

