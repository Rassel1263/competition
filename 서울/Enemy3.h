#pragma once
class Enemy3 : public CEnemy
{
public:
	Enemy3(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void SetImages() override;
	virtual void Attack(float deltaTime) override;
};

