#include "DXUT.h"
#include "CEnemy.h"

CEnemy::CEnemy(D3DXVECTOR2 pos)
{
	team = L"enemy";
	restTime = 1.0f;

	this->pos = pos;
	this->groundPos = pos.y;

	CreateCollider(D3DXVECTOR2(-60, 0), D3DXVECTOR2(60, 250), L"enemy", D3DCOLOR_ARGB(255, 0, 255, 0));
	nowScene->obm.AddObject(enemyUI = new EnemyUI(this));

	colorShader = new ColorShader();
	outlineShader = new OutlineShader();
}

void CEnemy::Update(float deltaTime)
{
	if (nowState)
		nowState->UpdateState(this, deltaTime);

	Unit::Update(deltaTime);
}

void CEnemy::Render()
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

void CEnemy::OnCollision(Collider & coli)
{
	if (coli.tag == L"playerbullet")
	{
		if (abs(groundPos - coli.obj->groundPos) >= 100) return;

		auto pBullet = static_cast<Bullet*>(coli.obj);

		if (pBullet->type == Bullet::Type::SNIPER)
			if(hit) nowScene->obm.AddObject(new Effect(L"Player/Explode_sniper", pBullet->pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));

		Hit(pBullet->damage, pBullet->attackVec);
	}
}


void CEnemy::Hit(float damage, D3DXVECTOR2 attackVec)
{
	if (hit) return;

	if (nowScene->player->powerUp)
		damage *= 1.3f;

	Unit::Hit(damage, attackVec);

	if (nowScene->player->specialIndex == -1)
	{
		nowScene->obm.AddObject(new Effect(L"Player/Hit1", pos + D3DXVECTOR2(0, 150) + nowScene->GetRandVec(-70, 70, -70, 70), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandNum(3, 6)));
	}
	else if (nowScene->player->specialIndex == 2)
	{
		nowScene->obm.AddObject(new Effect(L"Player/Explode_sniper", pos + D3DXVECTOR2(0, 150) + nowScene->GetRandVec(-70, 70, -70, 70), D3DXVECTOR2(0.3, 0.3), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));
		nowScene->obm.AddObject(new Effect(L"Player/item", pos + D3DXVECTOR2(0, 150) + nowScene->GetRandVec(-50, 50, -50, 50), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandNum(10, 20) * 0.1));
	}
	else
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandNum(10, 20) *0.1));

	nowScene->player->PlusCombo(1);
	nowScene->obm.AddObject(new Damage(pos + D3DXVECTOR2(0, 300), damage));

	if (ability.hp <= 0)
		SetState(EnemyDie::GetInstance());
}

void CEnemy::Destroy()
{
	moveRange->destroy = true;
	attackRange->destroy = true;
	enemyUI->destroy = true;
	nowScene->AddScore(nowScene->GetRandNum(1000, 2000));
	nowScene->enemyManager.SortEnemy(this);

	destroy = true;
}

bool CEnemy::Move(float deltaTime)
{
	D3DXVECTOR2 dir = { 0,0 };
	D3DXVECTOR2 distance = nowScene->player->pos - pos;
	D3DXVec2Normalize(&dir, &distance);

	if (!DetectRange(moveRange))
		return false;

	(dir.x > 0) ? ri.scale.x = 1 : ri.scale.x = -1;

	pos.x += dir.x * ability.speed * deltaTime;
	groundPos += dir.y * ability.speed/ 2 * deltaTime;

	return true;
}

void CEnemy::SetState(CState<CEnemy>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);

}
