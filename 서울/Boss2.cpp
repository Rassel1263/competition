#include "DXUT.h"
#include "Boss2.h"

Boss2::Boss2()
{
	SetImages();

	ability.SetAbility(1000, 100);

	hitTime = 0.1f;
	restTime = 0.5f;

	nowScene->obm.AddObject(moveRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-1000, -300), D3DXVECTOR2(1000, 300), D3DCOLOR_ARGB(255, 0, 0, 255), 500));
	CreateCollider(D3DXVECTOR2(-300, 0), D3DXVECTOR2(300, 500), L"enemy", D3DCOLOR_ARGB(255, 0, 255, 0));

	SetState(BossIdle::GetInstance());

	sp = 250.0f;
	maxSp = 250.0f;
}

void Boss2::Update(float deltaTime)
{
	CBoss::Update(deltaTime);
}

void Boss2::Render()
{
	CBoss::Render();
}

void Boss2::SetImages()
{
	Resize(Images::END);

	std::wstring filePath = L"Assets/Sprites/Unit/boss/Type2/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"Idle", 0.05f, true);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.05f, true);
	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.025f, false);
	GetSprite(Images::STUN).LoadAll(filePath + L"stun", 0.05, false);
	GetSprite(Images::DIE).LoadAll(filePath + L"DIE", 0.05, false);
	GetSprite(Images::ATTACK1).LoadAll(filePath + L"Attack1", 0.05, false);
	GetSprite(Images::ATTACK2).LoadAll(filePath + L"Attack2", 0.04, false);
	GetSprite(Images::ATTACKRUSH).LoadAll(filePath + L"AttackRush", 0.04, false);
	GetSprite(Images::ATTACKEND).LoadAll(filePath + L"AttackEnd", 0.04, false);
	GetSprite(Images::ATTACK3).LoadAll(filePath + L"Attack3", 0.05, false);
}

int Boss2::ChoosePattern()
{
	return nowScene->GetRandNum(1, 3);
}

bool Boss2::Pattern1(float deltaTime)
{
	if (!GetNowSprite().bAnimation)
		return false;

	if (GetNowSprite().scene == 18 && !onAttack)
	{
		nowScene->obm.AddObject(new AttackCollider(team, pos, D3DXVECTOR2(ri.scale.x * 200, 0), D3DXVECTOR2(-300, 0), D3DXVECTOR2(300, 300), 8, D3DXVECTOR2(100, 0), 0.0f, groundPos, 0.05f));
		onAttack = true;
	}
	else if (GetNowSprite().scene == 26 && !onAttack)
	{
		nowScene->obm.AddObject(new AttackCollider(team, pos, D3DXVECTOR2(ri.scale.x * 200, 0), D3DXVECTOR2(-300, 0), D3DXVECTOR2(300, 200), 8, D3DXVECTOR2(100, 0), 0.0f, groundPos, 0.05));
		onAttack = true;
	}
	else if (GetNowSprite().scene == 35 && !onAttack)
	{
		nowScene->obm.AddObject(new AttackCollider(team, pos, D3DXVECTOR2(ri.scale.x * 200, 0), D3DXVECTOR2(-300, 0), D3DXVECTOR2(300, 200), 8, D3DXVECTOR2(100, 300), 0.1f, groundPos, 0.05));
		onAttack = true;
	}
	else
		onAttack = false;

	return true;
}

bool Boss2::Pattern2(float deltaTime)
{
	if (!GetSprite(Images::ATTACKEND).bAnimation)
	{
		GetNowSprite().Reset();
		return false;
	}

	if (renderNum == IntEnum(Images::ATTACKRUSH))
	{
		if (!onAttack)
		{
			onAttack = true;
			nowScene->obm.AddObject(new AttackCollider(team, &pos, D3DXVECTOR2(0, 0), D3DXVECTOR2(-150, 0), D3DXVECTOR2(150, 200), 8, D3DXVECTOR2(300, 150), 0.3f, groundPos, GetNowSprite().aniMaxTime * GetNowSprite().szScene));
		}

		pos.x += ri.scale.x * 800 * deltaTime;
	}

	if (!GetNowSprite().bAnimation)
		SetAni(PlusEnum(Images, Images::ATTACK2, ++rushIndex));

	return true;
}

bool Boss2::Pattern3(float deltaTime)
{
	if (!GetNowSprite().bAnimation)
		return false;

	Camera::GetInstance().cameraQuaken = { 5, 5 };

	if (!onAttack)
	{

		onAttack = true;
		nowScene->obm.AddObject(new AttackCollider(team, pos, D3DXVECTOR2(0, 0), D3DXVECTOR2(-300, -200), D3DXVECTOR2(300, 400), 2, D3DXVECTOR2(20, 0), 0.0f, groundPos, GetNowSprite().aniMaxTime * GetNowSprite().szScene));
	}

	return true;
}
