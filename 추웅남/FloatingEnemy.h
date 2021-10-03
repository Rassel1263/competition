#pragma once
class FloatingEnemy : public CEnemy
{
public:
	FloatingEnemy(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Hit(float damage) override;
	virtual void Destroy() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void Attack(float deltaTime) override;
};

