#pragma once
class EnemyIdle : public CState<CEnemy>
{
public:
	static EnemyIdle* GetInstance();

	virtual void EnterState(CEnemy * obj) override;
	virtual void UpdateState(CEnemy * obj, float deltaTime) override;
	virtual void ExitState(CEnemy * obj) override;
};

class EnemyMove : public CState<CEnemy>
{
public:
	static EnemyMove* GetInstance();

	virtual void EnterState(CEnemy * obj) override;
	virtual void UpdateState(CEnemy * obj, float deltaTime) override;
	virtual void ExitState(CEnemy * obj) override;
};

class EnemyHit : public CState<CEnemy>
{
public:
	static EnemyHit* GetInstance();

	virtual void EnterState(CEnemy * obj) override;
	virtual void UpdateState(CEnemy * obj, float deltaTime) override;
	virtual void ExitState(CEnemy * obj) override;
};

class EnemyStun : public CState<CEnemy>
{
public:
	static EnemyStun* GetInstance();

	virtual void EnterState(CEnemy * obj) override;
	virtual void UpdateState(CEnemy * obj, float deltaTime) override;
	virtual void ExitState(CEnemy * obj) override;
};

class EnemyDie : public CState<CEnemy>
{
public:
	static EnemyDie* GetInstance();

	virtual void EnterState(CEnemy * obj) override;
	virtual void UpdateState(CEnemy * obj, float deltaTime) override;
	virtual void ExitState(CEnemy * obj) override;
};

class EnemyAttackReady : public CState<CEnemy>
{
public:
	static EnemyAttackReady* GetInstance();

	virtual void EnterState(CEnemy * obj) override;
	virtual void UpdateState(CEnemy * obj, float deltaTime) override;
	virtual void ExitState(CEnemy * obj) override;
};

class EnemyAttack : public CState<CEnemy>
{
public:
	static EnemyAttack* GetInstance();

	virtual void EnterState(CEnemy * obj) override;
	virtual void UpdateState(CEnemy * obj, float deltaTime) override;
	virtual void ExitState(CEnemy * obj) override;
};

class EnemyAttackEnd : public CState<CEnemy>
{
public:
	static EnemyAttackEnd* GetInstance();

	virtual void EnterState(CEnemy * obj) override;
	virtual void UpdateState(CEnemy * obj, float deltaTime) override;
	virtual void ExitState(CEnemy * obj) override;
};