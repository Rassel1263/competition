#include "DXUT.h"
#include "CBoss.h"

CBoss::CBoss()
{
	team = L"enemy";

	pos = D3DXVECTOR2(16000, -200);
	groundPos = pos.y;

	restTime = 0.5f;

	colorShader = new ColorShader();

	nowScene->spawnBoss = true;

	nowScene->obm.AddObject(new BossUI(this));
	nowScene->obm.AddObject(new BossIntro());

	outlineShader = new OutlineShader();
	superAromor = true;


}

void CBoss::Update(float deltaTime)
{
	UpdatePattern(deltaTime);
	SuperAromorUpdate(deltaTime);

	if (!nowScene->player->stop)
	{
		if (nowState)
			nowState->UpdateState(this, deltaTime);
	}

	Unit::Update(deltaTime);
}

void CBoss::Render()
{
	ri.pos = pos;
	shadow.Render(RenderInfo{ D3DXVECTOR2(pos.x, groundPos) });

	if (hit)
		colorShader->Render(colorShader, GetNowSprite(), ri);
	else if (superAromor)
		outlineShader->Render(outlineShader, GetNowSprite(), ri);
	else
		GetNowSprite().Render(ri);

	Object::Render();
}

void CBoss::OnCollision(Collider & coli)
{
	if (coli.tag == L"playerbullet")
	{
		if (abs(groundPos - coli.obj->groundPos) >= 100) return;

		auto pBullet = static_cast<Bullet*>(coli.obj);

		if (pBullet->type == Bullet::Type::SNIPER)
			nowScene->obm.AddObject(new Effect(L"Player/Explode_sniper", pBullet->pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));

		Hit(pBullet->damage, pBullet->attackVec);
	}
}

void CBoss::Hit(float damage, D3DXVECTOR2 attackVec)
{
	if (hit) return;

	Unit::Hit(damage, attackVec);

	if (nowScene->player->specialIndex == -1)
	{
		nowScene->obm.AddObject(new Effect(L"Player/Hit1", pos + nowScene->GetRandVec(-50, 50, -50, 50), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandNum(5, 8)));
	}
	else if (nowScene->player->specialIndex == 2)
	{
		nowScene->obm.AddObject(new Effect(L"Player/Explode_sniper", pos + nowScene->GetRandVec(-50, 50, -50, 50), D3DXVECTOR2(0.3, 0.3), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandNum(1, 2)));
	}
	else
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandNum(1, 2)));

	sp -= damage;

	if (sp <= 0.0f)
	{
		superAromor = false;
		sp = 0.0f;
	}

	nowScene->player->PlusCombo(1);

	if (ability.hp <= 0.0f)
		SetState(BossDie::GetInstance());
}

bool CBoss::Move(float deltaTime)
{
	D3DXVECTOR2 dir = { 0,0 };
	D3DXVECTOR2 distance = nowScene->player->pos - pos;
	D3DXVec2Normalize(&dir, &distance);

	if (!DetectRange(moveRange))
		return false;

	(dir.x > 0) ? ri.scale.x = 1 : ri.scale.x = -1;

	pos.x += dir.x * ability.speed * deltaTime;
	groundPos += dir.y * ability.speed / 2 * deltaTime;

	return true;
}

void CBoss::SuperAromorUpdate(float deltaTime)
{
	if (!superAromor)
	{
		spTimer += deltaTime;

		if (spTimer >= 5.0f)
		{
			superAromor = true;
			sp = maxSp;
			spTimer = 0.0f;
		}
	}
}

int CBoss::ChoosePattern()
{
	return 0;
}

void CBoss::UpdatePattern(float deltaTime)
{
	if (pattern == 0)
	{
		restTimer += deltaTime;

		if (restTimer >= restTime)
		{
			restTimer = 0.0f;
			pattern = ChoosePattern();
		}
	}
}
void CBoss::ResetPattern()
{
	onAttack = false;
	pattern = 0;
	rushIndex = 0;
}
void CBoss::SetState(CState<CBoss>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);
}
