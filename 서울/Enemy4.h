#pragma once
class Enemy4 : public CEnemy
{
public:
	Enemy4(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void SetImages() override;
	virtual void Attack(float deltaTime) override;
};

