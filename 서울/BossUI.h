#pragma once

class CBoss;
class BossUI : public Object
{
public:

	int index = 0;

	Sprite hpBck;
	Sprite hp;
	RenderInfo hpRI;

	Sprite spBck;
	Sprite sp;
	RenderInfo spRI;
	CBoss* boss = NULL;

	BossUI(CBoss* boss);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

