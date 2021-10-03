#include "DXUT.h"
#include "Enemy4.h"

Enemy4::Enemy4(D3DXVECTOR2 pos) : CEnemy(pos)
{
	enemyType = 4;
	power = 10;

	ability.SetAbility(70, 100);


	SetImages();

	nowScene->obm.AddObject(moveRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-800, -200), D3DXVECTOR2(800, 200), D3DCOLOR_ARGB(255, 0, 0, 255), 300));
	nowScene->obm.AddObject(attackRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-200, 0), D3DXVECTOR2(200, 200), D3DCOLOR_ARGB(255, 255, 0, 0), 100));

	SetState(EnemyIdle::GetInstance());
}

void Enemy4::Update(float deltaTime)
{
	CEnemy::Update(deltaTime);
}

void Enemy4::Render()
{
	CEnemy::Render();
}

void Enemy4::SetImages()
{
	Resize(CEnemy::Images::END);

	std::wstring path = L"Assets/Sprites/Unit/enemy/Type4/";

	GetSprite(CEnemy::Images::IDLE).LoadAll(path + L"Idle", 0.05f, true);
	GetSprite(CEnemy::Images::MOVE).LoadAll(path + L"move", 0.05f, true);
	GetSprite(CEnemy::Images::HIT).LoadAll(path + L"hit", 0.025f);
	GetSprite(CEnemy::Images::STUN).LoadAll(path + L"stun", 0.05f);
	GetSprite(CEnemy::Images::DIE).LoadAll(path + L"die", 0.05f);
	GetSprite(CEnemy::Images::ATTACKREADY).LoadAll(path + L"ready", 0.05f);
	GetSprite(CEnemy::Images::ATTACK).LoadAll(path + L"attack", 0.05f);
	GetSprite(CEnemy::Images::ATTACKEND).LoadAll(path + L"end", 0.05f);
}

void Enemy4::Attack(float deltaTime)
{
	if (!onAttack)
	{
		onAttack = true;
		nowScene->obm.AddObject(new AttackCollider(team, &pos, D3DXVECTOR2(0, 0), D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 200), 8, D3DXVECTOR2(200, 200), 0.1f, groundPos, GetNowSprite().aniMaxTime * GetNowSprite().szScene));
	}

	pos.x += ri.scale.x * 500 * deltaTime ;
}
