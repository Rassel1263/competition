#pragma once
class Mp : public Object
{
public:

	float angle = 0.0f;
	float turnSpeed = 0.0f;
	float turnTime = 0.0f;

	bool hit = false;

	float amount = 0.0f;

	Sprite spr;
	RenderInfo ri;

	Mp(D3DXVECTOR2 pos, float amount);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

