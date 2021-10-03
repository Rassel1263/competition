#pragma once
class BossIdle : public CState<CBoss>
{
public:
	static BossIdle* GetInstance();

	virtual void EnterState(CBoss * obj) override;
	virtual void UpdateState(CBoss * obj, float deltaTime) override;
	virtual void ExitState(CBoss * obj) override;
};

class BossMove : public CState<CBoss>
{
public:
	static BossMove* GetInstance();

	virtual void EnterState(CBoss * obj) override;
	virtual void UpdateState(CBoss * obj, float deltaTime) override;
	virtual void ExitState(CBoss * obj) override;
};

class BossHit : public CState<CBoss>
{
public:
	static BossHit* GetInstance();

	virtual void EnterState(CBoss * obj) override;
	virtual void UpdateState(CBoss * obj, float deltaTime) override;
	virtual void ExitState(CBoss * obj) override;
};

class BossStun : public CState<CBoss>
{
public:
	static BossStun* GetInstance();

	virtual void EnterState(CBoss * obj) override;
	virtual void UpdateState(CBoss * obj, float deltaTime) override;
	virtual void ExitState(CBoss * obj) override;
};

class BossDie : public CState<CBoss>
{
public:
	bool drawClear = false;
	float timer = 0.0f;

	static BossDie* GetInstance();

	virtual void EnterState(CBoss * obj) override;
	virtual void UpdateState(CBoss * obj, float deltaTime) override;
	virtual void ExitState(CBoss * obj) override;
};

class BossPaatern1 : public CState<CBoss>
{
public:
	static BossPaatern1* GetInstance();

	virtual void EnterState(CBoss * obj) override;
	virtual void UpdateState(CBoss * obj, float deltaTime) override;
	virtual void ExitState(CBoss * obj) override;
};

class BossPaatern2 : public CState<CBoss>
{
public:
	static BossPaatern2* GetInstance();

	virtual void EnterState(CBoss * obj) override;
	virtual void UpdateState(CBoss * obj, float deltaTime) override;
	virtual void ExitState(CBoss * obj) override;
};

class BossPaatern3 : public CState<CBoss>
{
public:
	static BossPaatern3* GetInstance();

	virtual void EnterState(CBoss * obj) override;
	virtual void UpdateState(CBoss * obj, float deltaTime) override;
	virtual void ExitState(CBoss * obj) override;
};