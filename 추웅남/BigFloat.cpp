#include "DXUT.h"
#include "BigFloat.h"

BigFloat::BigFloat(D3DXVECTOR2 pos) : FloatingEnemy(pos)
{
	type = Type::BigFloat;

	Resize(2);
	GetSprite(0).LoadAll(L"Assets/Sprites/enemy/typeboss1/enter", 0.05f, false);
	GetSprite(1).LoadAll(L"Assets/Sprites/enemy/typeboss1/move", 0.05f, true);
	SetAni(0);

	CreateCollider(D3DXVECTOR2(-500, -200), D3DXVECTOR2(500, 200), team);
	bCollider = false;


	bGun.resize(24);
	bGunInfo.resize(2);
	int cnt = 0;
	for (auto& spr : bGun)
	{
		spr.LoadAll(L"Assets/Sprites/enemy/Biggun/" + std::to_wstring(cnt), 0.05, true);
		cnt++;
	}

	sGun.resize(24);
	sGunInfo.resize(12);
	cnt = 0;
	for (auto& spr : sGun)
	{
		spr.LoadAll(L"Assets/Sprites/enemy/Smallgun/" + std::to_wstring(cnt), 0.05, true);
		cnt++;
	}

	bGunInfo[0].ri.pos = pos + D3DXVECTOR2(460, 90);
	bGunInfo[1].ri.pos = pos + D3DXVECTOR2(-200, 90);

	int size = 48;
	int i = 0;
	for (; i < 3; ++i)
		sGunInfo[i].ri.pos = pos + D3DXVECTOR2(-30 + i * size, 150);
	for (; i < 6; ++i)
		sGunInfo[i].ri.pos = pos + D3DXVECTOR2(-30 + (i - 3) * size, -20);
	for (; i < 9; ++i)
		sGunInfo[i].ri.pos = pos + D3DXVECTOR2(240 + (i - 6) * size, 150);
	for (; i < 12; ++i)
		sGunInfo[i].ri.pos = pos + D3DXVECTOR2(240 + (i - 9) * size, -20);

	nowScene->player->fallowCamera = false;
	nowScene->player->limitPos = pos + D3DXVECTOR2(1300, 500);
	Camera::GetInstance().destCameraPos = pos;
	Camera::GetInstance().destCameraScale = { 0.75f, 0.75f };

	nowScene->obm.AddObject(new BossIntro());
	nowScene->spawnBoss = true;

	ability.SetAbility(300, 0);

	attackTimer = 0.0f;
	attackTime = 0.0f;
}

void BigFloat::Update(float deltaTime)
{
	if (Intro(deltaTime)) return;
	if (Outro(deltaTime)) return;

	UpdatePattern(deltaTime);

	SetGunRotate(sGunInfo);
	SetGunRotate(bGunInfo);

	Unit::Update(deltaTime);
}

void BigFloat::Render()
{
	FloatingEnemy::Render();

	if (!intro)
	{
		GunRender(sGun, sGunInfo);
		GunRender(bGun, bGunInfo);
	}
}

void BigFloat::Hit(float damage)
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

void BigFloat::SetGunRotate(std::vector<GunInfo>& info)
{
	for (auto& spr : info)
	{
		int rotate = nowScene->GetAngleFromTarget(spr.ri.pos, target->pos);
		spr.renderNum = abs(rotate / (360 / 24) % 24);
	}
}

void BigFloat::GunRender(std::vector<Sprite>& gun, std::vector<GunInfo>& info)
{
	int size = info.size();

	for (int i = 0; i < size; ++i)
		gun[info[i].renderNum].Render(info[i].ri);
}

bool BigFloat::Intro(float deltaTime)
{
	if (!intro)
		return false;

	if (!GetNowSprite().bAnimation)
	{
		SetAni(1);
		intro = false;
		bCollider = true;
	}

	GetNowSprite().Update(deltaTime);
	return true;
}

bool BigFloat::Outro(float deltaTime)
{
	if (ability.hp <= 0)
	{

		if (outroTimer >= 6.0f)
		{
			GetNowSprite().color.a -= deltaTime;

			for (auto& spr : bGun)
				spr.color.a = GetNowSprite().color.a;

			for (auto& spr : sGun)
				spr.color.a = GetNowSprite().color.a;

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

void BigFloat::ChoosePattern()
{
	prevPattern = pattern;
	while (prevPattern == pattern)
		pattern = nowScene->GetRandNum(1, 3);
	attackTimer = 0.0f;

	if (pattern == 1)
	{
		gunIndx = 0;
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
		attackTime = 3.0f;
		shootInterval = 0.3f;
	}
}

void BigFloat::UpdatePattern(float deltaTime)
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

bool BigFloat::Pattern1(float deltaTime)
{
	if (attackTimer >= attackTime)
		return false;

	shootTimer += deltaTime;

	if (shootTimer >= shootInterval)
	{
		float angle = D3DXToRadian(nowScene->GetAngleFromTarget(sGunInfo.at(gunIndx).ri.pos, target->pos) + nowScene->GetRandNum(-10, 10));
		D3DXVECTOR2 fixPos = sGunInfo.at(gunIndx).ri.pos + D3DXVECTOR2(cosf(angle), sinf(angle)) * 20;
		nowScene->obm.AddObject(new Bullet(target, fixPos, 5, 600, angle, Bullet::Type::MACHINE));
		nowScene->obm.AddObject(new Effect(L"shoot_machinegun", fixPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
		SoundManager::GetInstance().Play("Machine");

		++gunIndx;

		if (gunIndx > 11)
			gunIndx = 0;

		shootTimer = 0.0f;
	}

	return true;
}

bool BigFloat::Pattern2(float deltaTime)
{
	if (attackTimer >= attackTime)
		return false;

	shootTimer += deltaTime;

	if (shootTimer >= shootInterval)
	{
		Camera::GetInstance().cameraQuaken = { 13, 13 };

		D3DXVECTOR2 playerPos = target->pos + nowScene->GetRandVec(-150, 150, -150, 150);
		auto lmabda = [=]
		{
			SoundManager::GetInstance().Play("Navalgun");
			nowScene->obm.AddObject(new Effect(L"onexplode", playerPos, D3DXVECTOR2(0.7, 0.7), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
			nowScene->obm.AddObject(new HitBox(playerPos, D3DXVECTOR2(-100, -100), D3DXVECTOR2(100, 100), 10, 0.1f));
		};

		nowScene->obm.AddObject(new AttackGuide(playerPos, D3DXVECTOR2(2, 2), 1, 1.5f, lmabda));

		shootTimer = 0.0f;
	}

	return true;
}

bool BigFloat::Pattern3(float deltaTime)
{
	if (attackTimer >= attackTime)
		return false;

	shootTimer += deltaTime;

	if (shootTimer >= shootInterval)
	{
		Camera::GetInstance().cameraQuaken = { 8, 8 };
		nowScene->obm.AddObject(new Bullet(target, pos, 15, nowScene->GetRandNum(4, 7) * 100, nowScene->GetRandNum(0, 360), Bullet::Type::TORPEDO));

		shootTimer = 0.0f;
	}

	return true;
}
