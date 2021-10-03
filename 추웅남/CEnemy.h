#pragma once
class CEnemy : public Unit
{
public:
	enum class Type
	{
		None,
		Float,
		Fly,
		BigFloat,
		BigFly,
	} type;

	float attackTime = 0.0f;
	float attackTimer = 0.0f;

	float turnSpeed = 0.0f;
	float turnTime = 0.0f;

public:
	CEnemy(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void Hit(float damage) override;
	virtual void Move(float deltaTime) override;
	virtual void Attack(float deltaTime) {};

	virtual void Destroy();
};

