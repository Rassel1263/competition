#pragma once
class BossBullet : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	float angle = 0.0f;
	float speed = 0.0f;
	float damage = 0.0f;

	float timer = 0.0f;
	int index = 0;

	std::function<void()> func = NULL;

	BossBullet(int index, D3DXVECTOR2 pos, float angle, float damage, float speed, float timer = 0.0f);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

