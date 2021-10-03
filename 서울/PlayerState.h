#pragma once
class PlayerIdle : public CState<Player>
{
public:
	static PlayerIdle* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerMove : public CState<Player>
{
public:
	static PlayerMove* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerJump : public CState<Player>
{
public:
	static PlayerJump* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerFall : public CState<Player>
{
public:
	static PlayerFall* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerLanding : public CState<Player>
{
public:
	static PlayerLanding* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerHit : public CState<Player>
{
public:
	static PlayerHit* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerStun : public CState<Player>
{
public:
	float timer = 0.0f;
	static PlayerStun* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerStandUp : public CState<Player>
{
public:
	static PlayerStandUp* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerDie : public CState<Player>
{
public:
	bool drawFail = false;

	float timer = 0.0f;

	static PlayerDie* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};


///////// АјАн

class PlayerJumpAttack : public CState<Player>
{
public:
	int combo = 0;
	int comboInput = 0;
	float timer = 0.0f;

	static PlayerJumpAttack* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerWeakAttack : public CState<Player>
{
public:
	int combo = 0;
	int comboInput = 0;
	float timer = 0.0f;

	static PlayerWeakAttack* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerWeakAttackEnd : public CState<Player>
{
public:
	static PlayerWeakAttackEnd* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerStrongAttack : public CState<Player>
{
public:
	static PlayerStrongAttack* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerSpecialAttack : public CState<Player>
{
public:
	static PlayerSpecialAttack* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};

class PlayerGrenade : public CState<Player>
{
public:
	static PlayerGrenade* GetInstance();

	virtual void EnterState(Player * obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player * obj) override;
};