#pragma once
class Unit : public Object
{
public:
	struct Ability
	{
		float hp = 0.0;
		float maxHp = 0.0f;
		float speed = 0.0f;

		void SetAbility(float hp , float speed)
		{
			this->hp = hp;
			this->maxHp = hp;
			this->speed = speed;
		}
	} ability; 

	std::vector<Sprite> sprites;

	Sprite shadow;

	RenderInfo ri;

	std::wstring team = L"";

	int renderNum = 0;

	bool onAttack = false;
	bool superAromor = false;

	bool hit = false;
	float hitTimer = 0.0f;
	float hitTime = 0.1f;

	ColorShader* colorShader = NULL;
	OutlineShader* outlineShader = NULL;

public:
	Unit();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void SetImages() = 0;
	virtual void Hit(float damage, D3DXVECTOR2 attackVec);
	
	bool Blink(float deltaTime, float amount);

	bool DetectRange(Range* range);

	Sprite& GetNowSprite();

	template <typename T>
	void SetAni(T n)
	{
		renderNum = IntEnum(n);
		GetNowSprite().Reset();
	}

	template <typename T>
	void Resize(T n)
	{
		sprites.resize(IntEnum(n));
	}

	template <typename T>
	Sprite& GetSprite(T n)
	{
		return sprites.at(IntEnum(n));	
	}
};

