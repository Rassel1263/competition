#pragma once
class Damage : public Object
{
public:
	std::vector<Sprite> spr;
	RenderInfo ri;

	float alpha = 1.0f;

	Damage(D3DXVECTOR2 pos, int damage);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

