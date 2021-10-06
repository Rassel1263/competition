#pragma once
class Coin : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	float timer = 5.0f;

	float angle = 0.0f;
	float speed = 0.0f;
	D3DXVECTOR2 destPos = { 0, 0 };

	Coin(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

