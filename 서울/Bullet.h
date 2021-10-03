#pragma once
class Bullet : public Object
{
public:
	enum class Type
	{
		BASIC,
		AIRSHOT,
		MACHINEGUN,
		SNIPER,
		EMACHINEGUN,
		ESNIPER,
		GRENADE,

		ROCK,
		GOLDROCK,
	} type;

	Sprite spr;
	RenderInfo ri;

	std::wstring tag = L"";

	D3DXVECTOR2 dir = {0.0f, 0.0f};
	float damage = 0.0f;
	float speed = 0.0f;
	D3DXVECTOR2 attackVec = { 0.0f, 0.0f };


public:
	Bullet(std::wstring tag, D3DXVECTOR2 pos, D3DXVECTOR2 dir, float damage, float speed, Type type, float groundPos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

