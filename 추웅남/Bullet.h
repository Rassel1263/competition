#pragma once
class Bullet : public Object
{
public:
	enum class Type
	{
		MACHINE,
		NAVAL,
		TORPEDO,
		MISSILE,
	} type;

	Sprite spr;
	RenderInfo ri;

	float angle = 0.0f;
	float speed = 0.0f;
	float damage = 0.0f;

	Unit* target = NULL;

	float turnSpeed = 0.0f;
	float turnTime = 0.0f;
	float startTime = 0.0f;
	float horming = false;

	std::wstring tag = L"";

	Bullet(Unit* target, D3DXVECTOR2 pos, float damage, float speed, float angle, Type type, float startTime = 0.0f, bool horming = false);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	void HormingSystem(float deltaTime);
};

