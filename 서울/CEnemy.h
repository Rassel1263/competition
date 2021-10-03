#pragma once
class CEnemy : public Unit
{
public:
	enum class Images
	{
		IDLE,
		MOVE,
		HIT,
		STUN,
		DIE,

		ATTACKREADY,
		ATTACK,
		ATTACKEND,

		END,
	};

	int enemyType = 0;

	float restTime = 0.0f;
	float restTimer = 0.0f;

	float power = 0.0f;

	CState<CEnemy>* nowState = NULL;

	Range* moveRange = NULL;
	Range* attackRange = NULL;

	EnemyUI *enemyUI = NULL;

public:
	CEnemy(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli);
	virtual void SetImages() = 0;
	virtual void Hit(float damage, D3DXVECTOR2 attackVec);
	void Destroy();

	bool Move(float deltaTime);

	virtual void Attack(float deltaTime) = 0;

	void SetState(CState<CEnemy>* nextState);
};

