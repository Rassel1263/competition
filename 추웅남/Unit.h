#pragma once
class Unit : public Object
{
public:
	struct Ability
	{
		float hp = 0.0f;
		float maxHp = 0.0f;
		float speed = 0.0f;

		void SetAbility(float hp, float speed)
		{
			this->hp = hp;
			this->maxHp = hp;
			this->speed = speed;
		}
	} ability;

	// ¿òÁ÷ÀÓ
	float curRotate = 0.0f;
	float curRadian = 0.0f;


	bool hit = false;
	float hitTimer = 0.0f;
	float hitTime = 0.1f;

	std::vector<Sprite> sprites;
	RenderInfo ri;
	int renderNum = 0;

	ColorShader* colorShader = NULL;


	std::wstring team = L"";
	Unit* target = NULL;

public:
	Unit();
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Hit(float damage);
	virtual void Move(float deltaTime);

	Sprite& GetNowSprite()
	{
		return sprites[renderNum];
	}

	void Resize(int n)
	{
		sprites.resize(n);
	}

	void SetAni(int n)
	{
		renderNum = n;
		sprites[n].Reset();
	}

	Sprite& GetSprite(int n)
	{
		return sprites[n];
	}

	void SetRotate(int rotate, int scene);

};

