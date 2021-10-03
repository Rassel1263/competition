#include "DXUT.h"
#include "Enemy2.h"

Enemy2::Enemy2(D3DXVECTOR2 pos) : CEnemy(pos)
{
	enemyType = 2;
	power = 10;

	ability.SetAbility(30, 100);


	SetImages();

	nowScene->obm.AddObject(moveRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-800, -200), D3DXVECTOR2(800, 200), D3DCOLOR_ARGB(255, 0, 0, 255), 300));
	nowScene->obm.AddObject(attackRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-400, 0), D3DXVECTOR2(400, 200), D3DCOLOR_ARGB(255, 255, 0, 0), 100));

	SetState(EnemyIdle::GetInstance());
}


void Enemy2::Update(float deltaTime)
{
	CEnemy::Update(deltaTime);
}

void Enemy2::Render()
{
	CEnemy::Render();
}

void Enemy2::SetImages()
{
	Resize(CEnemy::Images::END);

	std::wstring path = L"Assets/Sprites/Unit/enemy/Type2/";

	GetSprite(CEnemy::Images::IDLE).LoadAll(path + L"Idle", 0.05f, true);
	GetSprite(CEnemy::Images::MOVE).LoadAll(path + L"move", 0.05f, true);
	GetSprite(CEnemy::Images::HIT).LoadAll(path + L"hit", 0.025f);
	GetSprite(CEnemy::Images::STUN).LoadAll(path + L"stun", 0.05f);
	GetSprite(CEnemy::Images::DIE).LoadAll(path + L"die", 0.05f);
	GetSprite(CEnemy::Images::ATTACK).LoadAll(path + L"attack", 0.05f);
}

void Enemy2::Attack(float deltaTime)
{
	if (GetNowSprite().scene == 12 && !onAttack)
	{
		SoundManager::GetInstance().Play("EnemyAttack2");
		onAttack = true;
		nowScene->obm.AddObject(new Bullet(L"enemy", pos + D3DXVECTOR2(ri.scale.x * 30, 150), D3DXVECTOR2(ri.scale.x, 0), power, 1000, Bullet::Type::ROCK, groundPos));
	}
}
