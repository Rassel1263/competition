#include "DXUT.h"
#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(D3DXVECTOR2 pos) : CEnemy(pos)
{
	type = Type::Fly;

	Resize(24);

	for (int i = 0; i < 24; ++i)
		GetSprite(i).LoadAll(L"Assets/Sprites/enemy/type2/move/" + std::to_wstring(i), 0.05f, true);


	curRadian = D3DXToRadian(nowScene->GetAngleFromTarget(pos, target->pos));
	curRotate = -D3DXToDegree(curRadian) + 450;
	SetRotate(curRotate, 24);

	ability.SetAbility(20, 600);

	CreateCollider(D3DXVECTOR2(-70, -70), D3DXVECTOR2(70, 70), team);

	layer = 6;


	attackTime = 5.0f;

	shadow = new ColorShader();
}

void FlyingEnemy::Update(float deltaTime)
{
	if (ability.hp <= 0.0f)
		Destroy();
	else
		Move(deltaTime);

	groundPos = pos.y - 120;

	CEnemy::Update(deltaTime);
}

void FlyingEnemy::Render()
{
	ri.pos = pos;
	shadowRI.pos = D3DXVECTOR2(pos.x, groundPos);
	shadowRI.scale = D3DXVECTOR2(1, 1) * (groundPos / (pos.y - 120));

	shadow->Render(shadow, GetNowSprite(), shadowRI, D3DXVECTOR4(0, 0, 0, 0.5));

	if (hit)
		colorShader->Render(colorShader, GetNowSprite(), ri);
	else
		GetNowSprite().Render(ri);

	Object::Render();
}

void FlyingEnemy::Hit(float damage)
{
	CEnemy::Hit(damage);
}

void FlyingEnemy::Destroy()
{
	if (nowScene->GetRandNum(0, 2))
		nowScene->obm.AddObject(new Item(pos, nowScene->GetRandNum(0, 5)));

	nowScene->player->kill++;

	SoundManager::GetInstance().Play("Explo");
	nowScene->obm.AddObject(new Effect(L"onexplode", pos, D3DXVECTOR2(0.5, 0.5), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));

	nowScene->destScore += nowScene->GetRandNum(1000, 2000);

	CEnemy::Destroy();
}

void FlyingEnemy::Attack(float deltaTime)
{
	if (attackTimer >= attackTime)
	{
		ability.speed = 800;

		if (D3DXVec2Length(&(target->pos - pos)) < 550)
		{
			for(int i = 0; i < nowScene->curStage + 2; ++i)
				nowScene->obm.AddObject(new Bullet(target, pos, 8, 600, curRadian + D3DXToRadian(nowScene->GetRandNum(-30, 30)), Bullet::Type::MISSILE));

			attackTimer = 0.0f;
			ability.speed = 600;
		}
	}
}
