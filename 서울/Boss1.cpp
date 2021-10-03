#include "DXUT.h"
#include "Boss1.h"

Boss1::Boss1()
{
	SetImages();

	ability.SetAbility(500, 100);
	
	hitTime = 0.1f;
	restTime = 0.5f;

	nowScene->obm.AddObject(moveRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-1000, -300), D3DXVECTOR2(1000, 300), D3DCOLOR_ARGB(255, 0, 0, 255), 500));
	CreateCollider(D3DXVECTOR2(-200, 0), D3DXVECTOR2(200, 300), L"enemy", D3DCOLOR_ARGB(255, 0, 255, 0));

	sp = 150.0f;
	maxSp = sp;
	
	SetState(BossIdle::GetInstance());
}

void Boss1::Update(float deltaTime)
{
	CBoss::Update(deltaTime);
}

void Boss1::Render()
{
	CBoss::Render();
}

void Boss1::SetImages()
{
	Resize(Images::END);

	std::wstring filePath = L"Assets/Sprites/Unit/boss/Type1/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"Idle", 0.05f, true);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.05f, true);
	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.025f, false);
	GetSprite(Images::STUN).LoadAll(filePath + L"stun", 0.05, false);
	GetSprite(Images::DIE).LoadAll(filePath + L"DIE", 0.05, false);
	GetSprite(Images::ATTACK1).LoadAll(filePath + L"Attack1", 0.05, false);
	GetSprite(Images::ATTACK2).LoadAll(filePath + L"Attack2", 0.05, false);
}

int Boss1::ChoosePattern()
{
	D3DXVECTOR2 dir = { 0, 0 };
	D3DXVec2Normalize(&dir, &(nowScene->player->pos - pos));

	if (abs(dir.y) < 0.2)
		return 1;
	else
		return 2;
}

bool Boss1::Pattern1(float deltaTime)
{
	if (!GetNowSprite().bAnimation)
		return false;

	if (GetNowSprite().scene == 11 && !onAttack)
	{
		onAttack = true;
		nowScene->obm.AddObject(new Bullet(team, pos + D3DXVECTOR2(ri.scale.x * 50, 150), D3DXVECTOR2(ri.scale.x, 0), 10, 1000, Bullet::Type::GOLDROCK, groundPos));
	}

	return true;
}

bool Boss1::Pattern2(float deltaTime)
{
	if (!GetNowSprite().bAnimation)
		return false;

	if (GetNowSprite().scene == 8 && !onAttack)
	{
		onAttack = true;
		D3DXVECTOR2 playerPos = D3DXVECTOR2(nowScene->player->pos.x, nowScene->player->groundPos);
		auto lambda = [=] {nowScene->obm.AddObject(new AttackCollider(team, playerPos, D3DXVECTOR2(0, 0), D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 100), 10, D3DXVECTOR2(0, 1000), 1.0f, playerPos.y, 0.1f)); };
		SoundManager::GetInstance().Play("EnemyAttack3");
		nowScene->obm.AddObject(new Effect(L"enemy/magic", playerPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.1), 1, true, 0.07f, lambda, 6));
	}

	return true;
}

bool Boss1::Pattern3(float deltaTime)
{
	return false;
}
