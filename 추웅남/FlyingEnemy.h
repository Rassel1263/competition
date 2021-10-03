#pragma once
class FlyingEnemy : public CEnemy
{
public:
	float groundPos = 0.0f;

	RenderInfo shadowRI;

	ColorShader* shadow = NULL;

	FlyingEnemy(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Hit(float damage) override;
	virtual void Destroy() override;
	virtual void Attack(float deltaTime) override;
};

