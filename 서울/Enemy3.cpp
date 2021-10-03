#include "DXUT.h"
#include "Enemy3.h"

Enemy3::Enemy3(D3DXVECTOR2 pos)  :CEnemy(pos)
{
	enemyType = 2;
	power = 10;

	ability.SetAbility(20, 100);


	SetImages();

	nowScene->obm.AddObject(moveRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-800, -200), D3DXVECTOR2(800, 200), D3DCOLOR_ARGB(255, 0, 0, 255), 300));
	nowScene->obm.AddObject(attackRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-500, 0), D3DXVECTOR2(500, 200), D3DCOLOR_ARGB(255, 255, 0, 0), 300));

	SetState(EnemyIdle::GetInstance());
}

void Enemy3::Update(float deltaTime)
{
	CEnemy::Update(deltaTime);
}

void Enemy3::Render()
{
	CEnemy::Render();
}

void Enemy3::SetImages()
{
	Resize(CEnemy::Images::END);

	std::wstring path = L"Assets/Sprites/Unit/enemy/Type3/";

	GetSprite(CEnemy::Images::IDLE).LoadAll(path + L"Idle", 0.05f, true);
	GetSprite(CEnemy::Images::MOVE).LoadAll(path + L"move", 0.05f, true);
	GetSprite(CEnemy::Images::HIT).LoadAll(path + L"hit", 0.025f);
	GetSprite(CEnemy::Images::STUN).LoadAll(path + L"stun", 0.05f);
	GetSprite(CEnemy::Images::DIE).LoadAll(path + L"die", 0.05f);
	GetSprite(CEnemy::Images::ATTACK).LoadAll(path + L"attack", 0.05f);
}

void Enemy3::Attack(float deltaTime)
{
	if (GetNowSprite().scene == 8 && !onAttack)
	{
		SoundManager::GetInstance().Play("EnemyAttack3");
		onAttack = true;
		D3DXVECTOR2 playerPos = D3DXVECTOR2(nowScene->player->pos.x, nowScene->player->groundPos);
		auto lambda = [=] {nowScene->obm.AddObject(new AttackCollider(team, playerPos, D3DXVECTOR2(0, 0), D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 200), power, D3DXVECTOR2(0, 1000), 1.0f, playerPos.y, 0.1f)); };
		nowScene->obm.AddObject(new Effect(L"enemy/magic", playerPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.1), 1, true, 0.1f, lambda, 6));
	}
}
