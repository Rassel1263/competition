#pragma once
class Player : public Unit
{
public:
	bool intro = true;
	bool stop = false;

	int kill = 0;

	int speedLevel = 1;
	D3DXVECTOR2 prevPos = { 0, 0 };

	float destSpeed = 0.0f;
	float dps = 0.0f;

	bool drawGameOver = false;

	// 카메라
	bool fallowCamera = true;
	float targitTimer = 0.0f;

	D3DXVECTOR2 limitPos = { 2000, 300 };

	std::vector<CWeapon*> weapons;

	// 스킬
	bool skill1 = false;
	float skill1Timer = 0.0f;
	float skill1CoolTime = 10.0;
	float skill1CoolTimer = 0.0f;

	float skill2CoolTime = 20.0f;
	float skill2CoolTimer = 0.0f;

	// 효과
	bool speedUp = false;
	float speedUpTime = 0.0f;

	bool speedDown = false;
	float speedDownTime = 0.0f;

	bool invincible = false;
	float invincibleTime = 0.0f;

	bool god = false;

	Unit* prevTarget = NULL;

public:
	Player();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void Hit(float damage) override;
	virtual void Move(float deltaTime);

	void SetTarget(CEnemy::Type type);
	void WeaponControll(float deltaTime);
	void CameraControll(float deltaTime);

	void SkillControll(float deltaTime);

	void GetEffective(int index);
	void UpdateEffective(float deltaTime);

};

