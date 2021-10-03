#pragma once

class CEnemy;
class EnemyUI : public Object
{
public:
	CEnemy* enemy = NULL;

	Sprite hpBck;
	Sprite hp;
	RenderInfo hpRI;

	EnemyUI(CEnemy* enemy);

	virtual void Update(float deltaTime);
	virtual void Render() override;
};

