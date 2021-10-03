#pragma once
class BigFly : public FlyingEnemy
{
public:
	bool intro = true;
	BigFly(D3DXVECTOR2 pos);

	// 패턴
	int prevPattern = 0;
	int pattern = 0;
	float restTimer = 0.0f;

	float shootTimer = 0.0f;
	float shootInterval = 0.0f;

	// 아웃트로
	float outroTimer = 0.0f;
	float effectTime = 1.0f;
	float effectTimer = 0.0f;
	float stopTime = 1.0f;

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Hit(float damage);

	bool Intro(float deltaTime);
	bool Outro(float deltaTime);

	void ChoosePattern();
	void UpdatePattern(float deltaTime);
	bool Pattern1(float deltaTime);
	bool Pattern2(float deltaTime);
	bool Pattern3(float deltaTime);

};

