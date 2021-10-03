#pragma once

class EnhanceData : public Singleton<EnhanceData>
{
public:
	std::vector<bool> enhance;

	void Init() 
	{
		enhance.resize(6);

		for (int i = 0; i < 6; ++i)
			enhance[i] = false;
	}

	void SetEnhance(int n)
	{
		enhance[n] = true;
	}

	void GetEnhance(std::vector<bool>& vec)
	{
		std::copy(enhance.begin(), enhance.end(), std::back_inserter(vec));
	}
};

class Player : public Unit
{
public:
	enum class Images
	{
		IDLE,
		MOVE,
		JUMP,
		FALL,
		LANDING,
		HIT,
		STUN,
		STANDUP,
		DIE,

		JUMPATTACK1,
		JUMPATTACK2,
		JUMPATTACK3,

		WEAKATTACK1,
		WEAKATTACK2,
		WEAKATTACK3,
		WEAKATTACK4,
		WEAKATTACKEND,

		STRONGATTACK,

		GRENADE,

		SLIDE,
		GUNKATA,
		MOVESHOT,
		MACHINEGUN,
		SNIPER,
		NUCLEAR,

		END,
	};

	CState<Player>* nowState = NULL;

	std::vector<bool> skillEnhance;

	float mp = 0.0f;
	float maxMp = 100.0f;

	float healTime = 0.0f;
	float healMaxTime = 0.0f;

	bool fallowCamera = true;

	bool jump = false;
	bool jumpAttack = false;

	bool invincible = false;
	bool stop = true;

	// 아이템
	bool powerUp = false;
	float powerUpTime = 0.0f;
	bool grenade = false;

	// 콤보
	int combo = 0;
	int prevCombo = 0;
	int maxCombo = 0;
	float comboInterval = 0.0f;

	std::vector<std::string> comboInputs;
	float comboInputTimer = 0.0f;
	bool specialAttack = false;
	int specialIndex = 0;

	float cancelTime = 0.0f;
	bool cancel = false;

	float attackTime = 0.0f;
	float attackTimer = 0.0f;

	bool nuclear = false;
	float nuclearTime = 0.0f;

	bool afterImage = false;
	float afterImageTime = 0.0f;
	float afterImageTimer = 0.0f;
public:
	Player();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void SetImages()  override;

	virtual void Hit(float damage, D3DXVECTOR2 attackVec) override;

	// 콤보
	void Combo(float deltaTime);
	void InputComboCheck();
	void InputCombo(unsigned char c, std::string name);
	void ComboCheck();
	void ComboChecking(int specialIndex, int inputAmount, ...);

	// 스킬
	void SetSpecialAttack(Images image, float atkScene, float afterImageTime, float mp);
	void SetCancel();
	void CancleUpdate(float deltaTime);

	void PlusHp(int value);
	void PlusMp(int value);
	void PlusCombo(int n);


	// 아이템
	void GetItem(int index);
	void UpdateEfftive(float deltaTime);

	void CreateBullet(D3DXVECTOR2 offset, float damage, float speed, Bullet::Type type, bool jumpshot = false);

	void CameraControll();

	bool Move(float deltaTime, bool moveShot = false);

	void SetState(CState<Player>* nextState);
};

