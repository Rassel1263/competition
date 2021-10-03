#include "DXUT.h"
#include "Enemy1.h"

Enemy1::Enemy1(D3DXVECTOR2 pos) : CEnemy(pos)
{
	enemyType = 1;
	power = 5;

	ability.SetAbility(40, 100);


	SetImages();

	nowScene->obm.AddObject(moveRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-800, -200), D3DXVECTOR2(800, 200), D3DCOLOR_ARGB(255, 0, 0, 255), 300));
	nowScene->obm.AddObject(attackRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-200, 0), D3DXVECTOR2(200, 200), D3DCOLOR_ARGB(255, 255, 0, 0), 100));

	SetState(EnemyIdle::GetInstance());
}


void Enemy1::Update(float deltaTime)
{
	CEnemy::Update(deltaTime);
}

void Enemy1::Render()
{
	CEnemy::Render();
}

void Enemy1::SetImages()
{
	Resize(CEnemy::Images::END);

	std::wstring path = L"Assets/Sprites/Unit/enemy/Type1/";

	GetSprite(CEnemy::Images::IDLE).LoadAll(path + L"Idle", 0.05f, true);
	GetSprite(CEnemy::Images::MOVE).LoadAll(path + L"move", 0.05f, true);
	GetSprite(CEnemy::Images::HIT).LoadAll(path + L"hit", 0.025f);
	GetSprite(CEnemy::Images::STUN).LoadAll(path + L"stun", 0.05f);
	GetSprite(CEnemy::Images::DIE).LoadAll(path + L"die", 0.05f);
	GetSprite(CEnemy::Images::ATTACK).LoadAll(path + L"attack", 0.05f);
}

void Enemy1::Attack(float deltaTime)
{
	if (GetNowSprite().scene == 7 && !onAttack)
	{
		onAttack = true;

		SoundManager::GetInstance().Play("EnemyAttack1");
		nowScene->obm.AddObject(new AttackCollider(team, pos, D3DXVECTOR2(ri.scale.x * 100, 0), D3DXVECTOR2(-50, 0), D3DXVECTOR2(50, 200), power, D3DXVECTOR2(100, 0), 0.0f, groundPos, 0.1f));
	}
}
