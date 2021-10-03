#pragma once
class HitBox : public Object
{
public:

	float timer = 0.0f;
	float damage = 0.0f;

	HitBox(D3DXVECTOR2 pos, D3DXVECTOR2 min, D3DXVECTOR2 max, float damage, float time);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

