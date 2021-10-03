#pragma once
class CBoss : public Unit
{
public:
	enum class Images
	{
		IDLE,
		MOVE,
		HIT,
		STUN,
		DIE,

		ATTACK1,
		ATTACK2,
		ATTACKRUSH,
		ATTACKEND,
		ATTACK3,

		END
	};

	int pattern = 0;
	int rushIndex = 0;

	float restTime = 0.0f;
	float restTimer = 0.0f;

	float sp = 0;
	float maxSp = 0;
	float spTimer = 0.0f;


	Range* moveRange = NULL;

	CState<CBoss>* nowState = NULL;
public:
	CBoss();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void SetImages() = 0;
	virtual void Hit(float damage, D3DXVECTOR2 attackVec);

	bool Move(float deltaTime);

	void SuperAromorUpdate(float deltaTime);

	virtual int ChoosePattern();
	void UpdatePattern(float deltaTime);

	virtual bool Pattern1(float deltaTime) = 0;
	virtual bool Pattern2(float deltaTime) = 0;
	virtual bool Pattern3(float deltaTime) = 0;

	void ResetPattern();

	void SetState(CState<CBoss>* nextState);


};

