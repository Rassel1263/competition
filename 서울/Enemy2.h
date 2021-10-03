#pragma once
class Enemy2 : public CEnemy
{
public:
	Enemy2(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void SetImages() override;
	virtual void Attack(float deltaTime) override;
};

