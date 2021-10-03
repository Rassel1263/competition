#include "DXUT.h"
#include "BigFly.h"

BigFly::BigFly(D3DXVECTOR2 pos) : FlyingEnemy(pos)
{
	this->groundPos = pos.y;
	this->pos.y += 1000;

	nowScene->spawnBoss = true;

	CreateCollider(D3DXVECTOR2(-500, -200), D3DXVECTOR2(500, 200), team);
	bCollider = false;

	type = Type::BigFly;

	Resize(8);

	for (int i = 0; i < 8; ++i)
		GetSprite(i).LoadAll(L"Assets/Sprites/enemy/typeBoss2/" + std::to_wstring(i), 0.05f, true);
	SetAni(4);

	nowScene->player->fallowCamera = false;
	nowScene->player->limitPos = pos + D3DXVECTOR2(1300, 500);
	Camera::GetInstance().destCameraPos = pos;
	Camera::GetInstance().destCameraScale = { 0.75f, 0.75f };

	nowScene->obm.AddObject(new BossIntro());

	ability.SetAbility(300, 0);

	attackTimer = 0.0f;
	attackTime = 0.0f;
}

void BigFly::Update(float deltaTime)
{
	if (Intro(deltaTime)) return;
	if (Outro(deltaTime)) return;

	UpdatePattern(deltaTime);

	Unit::Update(deltaTime);
}

void BigFly::Render()
{
	FlyingEnemy::Render();
}

void BigFly::Hit(float damage)
{
	if (hit) return;

	Unit::Hit(damage);

	if (ability.hp <= 0)
	{
		Camera::GetInstance().destCameraScale = { 1.5, 1.5 };
		nowScene->stopTime = true;
		nowScene->player->stop = true;
		nowScene->player->bCollider = false;
		hit = false;
	}
}

bool BigFly::Intro(float deltaTime)
{
	if (!intro)
		return false;

	if (pos.y >= groundPos + 150)
		pos.y -= deltaTime * 200;
	else
	{
		intro = false;
		bCollider = true;
	}

	GetNowSprite().Update(deltaTime);

	return true;
}

bool BigFly::Outro(float deltaTime)
{
	if (ability.hp <= 0)
	{
		if (outroTimer >= 6.0f)
		{
			GetNowSprite().color.a -= deltaTime;

			if (GetNowSprite().color.a <= 0.0f)
			{
				SoundManager::GetInstance().StopAll();
				SoundManager::GetInstance().Play("win");
				nowScene->player->fallowCamera = true;
				nowScene->player->stop = false;
				Camera::GetInstance().destCameraScale = { 1, 1 };
				nowScene->destScore += 10000;

				nowScene->enemyManager.SortEnemy(this, type);
				nowScene->miniMap->SortMiniObj(this);

				if (stopTime > 0.0f)
					stopTime -= deltaTime;
				{
					nowScene->obm.AddObject(new StageFont(StageFont::Type::CLEAR));
					destroy = true;
				}
			}
		}
		else
		{
			outroTimer += deltaTime;
			effectTimer += deltaTime;

			if (effectTimer >= effectTime)
			{
				effectTimer = 0.0f;
				effectTime -= effectTime / 5;

				float randScale = nowScene->GetRandNum(10, 20) * 0.05f;
				nowScene->obm.AddObject(new Effect(L"onexplode", pos + nowScene->GetRandVec(-500, 500, -200, 200), D3DXVECTOR2(randScale, randScale), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
				SoundManager::GetInstance().Play("Explo");
				Camera::GetInstance().cameraQuaken = D3DXVECTOR2(5, 5);
			}
		}

		return true;
	}

	return false;
}

void BigFly::ChoosePattern()
{
	prevPattern = pattern;
	while (prevPattern == pattern)
		pattern = nowScene->GetRandNum(1, 3);
	attackTimer = 0.0f;

	if (pattern == 1)
	{
		attackTime = 3.0f;
		shootInterval = 0.1f;
	}
	else if (pattern == 2)
	{
		attackTime = 3.0f;
		shootInterval = 0.5f;
	}
	else if (pattern == 3)
	{
		attackTime = 5.0f;
		shootInterval = 1.0f;
	}
}

void BigFly::UpdatePattern(float deltaTime)
{
	bool bPattern = false;

	if (pattern == 1)
		bPattern = Pattern1(deltaTime);
	else if (pattern == 2)
		bPattern = Pattern2(deltaTime);
	else if (pattern == 3)
		bPattern = Pattern3(deltaTime);

	if (!bPattern)
	{
		restTimer += deltaTime;

		if (restTimer >= 0.5f)
		{
			restTimer = 0.0f;
			ChoosePattern();
		}
	}
	else
		attackTimer += deltaTime;
}

bool BigFly::Pattern1(float deltaTime)
{
	if (attackTimer >= attackTime)
		return false;

	Move(deltaTime);

	shootTimer += deltaTime;

	if (shootTimer >= shootInterval)
	{
		int index = nowScene->GetRandNum(1, 3);

		if(index == 1)
			nowScene->obm.AddObject(new Bullet(target, pos, 5, nowScene->GetRandNum(70, 90) * 10, D3DXToRadian(nowScene->GetRandNum(0, 360)), Bullet::Type::MACHINE));
		else if(index == 2)
			nowScene->obm.AddObject(new Bullet(target, pos, 10, nowScene->GetRandNum(3, 5) * 100, D3DXToRadian(nowScene->GetRandNum(0, 360)), Bullet::Type::TORPEDO));
		else if(index == 3)
			nowScene->obm.AddObject(new Bullet(target, pos, 10, nowScene->GetRandNum(4, 6) * 100, D3DXToRadian(nowScene->GetRandNum(0, 360)), Bullet::Type::MISSILE));

		shootTimer = 0.0f;
	}

	return true;
}

bool BigFly::Pattern2(float deltaTime)
{
	if (attackTimer >= attackTime)
		return false;

	shootTimer += deltaTime;

	if (shootTimer >= shootInterval)
	{
		Camera::GetInstance().cameraQuaken = { 13, 13 };

		D3DXVECTOR2 playerPos = target->pos + nowScene->GetRandVec(-150, 150, -150, 150);
		int randScale = nowScene->GetRandNum(1, 6) * 0.5f;

		auto lmabda = [=]
		{
			SoundManager::GetInstance().Play("Explo");
			nowScene->obm.AddObject(new Effect(L"onexplode", playerPos, D3DXVECTOR2(randScale, randScale) * 0.4, D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
			nowScene->obm.AddObject(new HitBox(playerPos, D3DXVECTOR2(-100, -100), D3DXVECTOR2(100, 100), 10, 0.1f));
		};

		nowScene->obm.AddObject(new AttackGuide(playerPos, D3DXVECTOR2(randScale, randScale), 1, randScale * 0.5, lmabda));

		shootTimer = 0.0f;
	}

	return true;
}

bool BigFly::Pattern3(float deltaTime)
{
	if (attackTimer >= attackTime)
		return false;

	shootTimer += deltaTime;

	if (shootTimer >= shootInterval)
	{
		Camera::GetInstance().cameraQuaken = { 13, 13 };

		D3DXVECTOR2 playerPos = D3DXVECTOR2(0, target->pos.y)+ nowScene->GetRandVec(0, 0, -3, 3) * 100;

		auto lmabda = [=]
		{
			for (int i = 0; i < 8; ++i)
			{
				SoundManager::GetInstance().Play("Explo");
				nowScene->obm.AddObject(new Effect(L"onexplode", D3DXVECTOR2(-1800 + i * 400, playerPos.y), D3DXVECTOR2(0.7, 0.7), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
			}

			nowScene->obm.AddObject(new HitBox(playerPos, D3DXVECTOR2(-2000, -200), D3DXVECTOR2(2000, 200), 10, 0.1f));
		};

		nowScene->obm.AddObject(new AttackGuide(playerPos, D3DXVECTOR2(1, 1), 2, 2.5f, lmabda));

		shootTimer = 0.0f;
	}

	return true;
}
