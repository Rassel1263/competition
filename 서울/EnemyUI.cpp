#include "DXUT.h"
#include "EnemyUI.h"

EnemyUI::EnemyUI(CEnemy * enemy)
{
	this->enemy = enemy;
	hpBck.LoadAll(L"Assets/Sprites/UI/Enemy/enemyHpBck.png");
	hp.LoadAll(L"Assets/Sprites/UI/Enemy/enemyHp.png");
}

void EnemyUI::Update(float deltaTime)
{
	hp.widthRtaio = enemy->ability.hp / enemy->ability.maxHp;
	hpRI.pos = enemy->pos + D3DXVECTOR2(0, -50);
}

void EnemyUI::Render()
{
	hpBck.Render(RenderInfo{ hpRI });
	hp.Render(RenderInfo{ D3DXVECTOR2(hpRI.pos.x - 2, hpRI.pos.y - 3)});
}
