#include "DXUT.h"
#include "Weapon.h"

CWeapon::CWeapon(Unit* owner)
{
	this->owner = owner;
}

void CWeapon::Update(float deltaTime)
{
	if (shootTimer < shootInterval)
		shootTimer += deltaTime;
	else
		shootTimer = shootInterval;
}

MachineGun::MachineGun(Unit* owner) : CWeapon(owner)
{
	bulletAmount = 30;
	bulletMaxAmout = 30;

	shootInterval = 0.1f;

	reloadTime = 5.0f;

	speed = 2000;
	damage = 5;

}

void MachineGun::Update(float deltaTime)
{
	if (reload)
	{
		reloadTimer += deltaTime;

		if (reloadTimer >= reloadTime)
		{
			if(owner->team == L"player")
				SoundManager::GetInstance().Play("reload");

			reload = false;
			bulletAmount = bulletMaxAmout;
			reloadTimer = 0.0f;
		}
	}

	CWeapon::Update(deltaTime);
}

void MachineGun::Shoot(float angle)
{
	if (bulletAmount > 0)
	{
		if (shootTimer >= shootInterval)
		{
			Camera::GetInstance().cameraQuaken = { 2, 2 };
			SoundManager::GetInstance().Play("Machine");

			if (!nowScene->player->skill1)
				bulletAmount--;
			nowScene->obm.AddObject(new Bullet(owner->target, owner->pos, damage, speed, D3DXToRadian(angle), Bullet::Type::MACHINE));
			nowScene->obm.AddObject(new Effect(L"shoot_machinegun", owner->pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));

			shootTimer = 0.0f;
		}
	}
	else
	{
		reload = true;
		nowScene->msgBox->SpawnMsg(L"obtainBullet", 1);
	}
}

NavanGun::NavanGun(Unit* owner) : CWeapon(owner)
{
	bulletAmount = 5;
	bulletMaxAmout = 5;

	shootInterval = 1.0f;

	reloadTime = 1.0f;

	speed = 3000;

	damage = 10;
}

void NavanGun::Update(float deltaTime)
{
	if (bulletAmount < bulletMaxAmout)
	{
		reloadTimer += deltaTime;

		if (reloadTimer >= reloadTime)
		{
			reloadTimer = 0.0f;
			bulletAmount++;
		}
	}

	CWeapon::Update(deltaTime);
}

void NavanGun::Shoot(float angle)
{
	if (bulletAmount > 0)
	{
		if (shootTimer >= shootInterval)
		{
			SoundManager::GetInstance().Play("Navalgun");
			Camera::GetInstance().cameraQuaken = { 5, 5 };

			nowScene->obm.AddObject(new Bullet(owner->target, owner->pos, damage, speed, D3DXToRadian(angle), Bullet::Type::NAVAL));
			nowScene->obm.AddObject(new Effect(L"shoot_navalgun", owner->pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));

			bulletAmount--;

			shootTimer = 0.0f;
		}
	}
	else
		nowScene->msgBox->SpawnMsg(L"obtainBullet", 1);
}

TorpedoLauncher::TorpedoLauncher(Unit* owner) : CWeapon(owner)
{
	bulletAmount = 5;
	bulletMaxAmout = 15;

	shootInterval = 1.0f;

	speed = 800;

	damage = 15;
}

void TorpedoLauncher::Update(float deltaTime)
{
	CWeapon::Update(deltaTime);
}

void TorpedoLauncher::Shoot(float angle)
{
	if (bulletAmount > 0)
	{
		if (shootTimer >= shootInterval)
		{
			SoundManager::GetInstance().Play("Missile");
			Camera::GetInstance().cameraQuaken = { 5, 5 };

			nowScene->obm.AddObject(new Bullet(owner->target, owner->pos, damage, speed, D3DXToRadian(angle), Bullet::Type::TORPEDO, 0.5f, true));
			bulletAmount--;

			shootTimer = 0.0f;
		}
	}
	else
		nowScene->msgBox->SpawnMsg(L"obtainBullet", 1);
}

MissileLauncher::MissileLauncher(Unit* owner) : CWeapon(owner)
{
	bulletAmount = 5;
	bulletMaxAmout = 15;

	shootInterval = 1.0f;

	speed = 1000;

	damage = 15;
}

void MissileLauncher::Update(float deltaTime)
{
	CWeapon::Update(deltaTime);
}

void MissileLauncher::Shoot(float angle)
{
	if (bulletAmount > 0)
	{
		if (shootTimer >= shootInterval)
		{
			SoundManager::GetInstance().Play("Missile");
			Camera::GetInstance().cameraQuaken = { 5, 5 };

			nowScene->obm.AddObject(new Effect(L"shoot_missile", owner->pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0), 1, true, 0.05f));;
			nowScene->obm.AddObject(new Bullet(owner->target, owner->pos, damage, speed, D3DXToRadian(angle), Bullet::Type::MISSILE, 0.5f, true));
			bulletAmount--;

			shootTimer = 0.0f;
		}
	}
	else 
		nowScene->msgBox->SpawnMsg(L"obtainBullet", 1);
}
