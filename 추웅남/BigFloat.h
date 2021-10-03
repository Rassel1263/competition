#pragma once
class BigFloat : public FloatingEnemy
{
public:
	bool intro = true;
	BigFloat(D3DXVECTOR2 pos);

	// 패턴
	int prevPattern = 0;
	int pattern = 0;
	float restTimer = 0.0f;

	float shootTimer = 0.0f;
	float shootInterval = 0.0f;

	int gunIndx = 0;


	// 아웃트로
	float outroTimer = 0.0f;
	float effectTime = 1.0f;
	float effectTimer = 0.0f;

	float stopTime = 1.0f;

	// 무기
	struct GunInfo
	{
		RenderInfo ri;
		int renderNum = 0;
	};

	std::vector<Sprite> bGun;
	std::vector<GunInfo> bGunInfo;

	std::vector<Sprite> sGun;
	std::vector<GunInfo> sGunInfo;


	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Hit(float damage) override;

	void SetGunRotate(std::vector<GunInfo>& info);
	void GunRender(std::vector<Sprite>& gun, std::vector<GunInfo>& info);

	bool Intro(float deltaTime);
	bool Outro(float deltaTime);

	void ChoosePattern();
	void UpdatePattern(float deltaTime);
	bool Pattern1(float deltaTime);
	bool Pattern2(float deltaTime);
	bool Pattern3(float deltaTime);
};

