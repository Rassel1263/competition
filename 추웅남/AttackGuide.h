#pragma once
class AttackGuide : public Object
{
public:
	Sprite bck;
	RenderInfo bckRI;

	Sprite spr;
	RenderInfo ri;


	std::function<void()> func;

	float timer = 0.0f;
	float maxTime = 0.0f;
	int index = 0;

	AttackGuide(D3DXVECTOR2 pos, D3DXVECTOR2 scale, int index, float time ,std::function<void()> func = NULL);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

