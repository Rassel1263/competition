#pragma once

class Unit;
class CWeapon
{
public:
	float bulletAmount = 0;
	float bulletMaxAmout = 0;

	float shootTimer = 0.0f;
	float shootInterval = 0.0f;
	
	float damage = 0.0f;
	float speed = 0.0f;

	Unit* owner = NULL;

public:
	CWeapon(Unit* owner);
	virtual void Update(float deltaTime);
	virtual void Shoot(float angle) = 0;
};

class MachineGun : public CWeapon
{
public:
	bool reload = false;
	float reloadTime = 5.0f;
	float reloadTimer = 0.0f;

public:
	MachineGun(Unit* owner);
	virtual void Update(float deltaTime) override;
	virtual void Shoot(float angle);
};

class NavanGun : public CWeapon
{
public:
	float reloadTime = 1.0f;
	float reloadTimer = 0.0f;

public:
	NavanGun(Unit* owner);
	virtual void Update(float deltaTime) override;
	virtual void Shoot(float angle);
};

class TorpedoLauncher : public CWeapon
{

public:
	TorpedoLauncher(Unit* owner);
	virtual void Update(float deltaTime) override;
	virtual void Shoot(float angle);
};

class MissileLauncher : public CWeapon
{

public:
	MissileLauncher(Unit* owner);
	virtual void Update(float deltaTime) override;
	virtual void Shoot(float angle);
};


