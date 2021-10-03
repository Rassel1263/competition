#include "DXUT.h"
#include "Player.h"

Player::Player()
{
	team = L"player";

	pos.y = -150;
	groundPos = -150;

	SetImages();

	ability.SetAbility(100, 700);

	colorShader = new ColorShader();
	outlineShader = new OutlineShader();

	EnhanceData::GetInstance().GetEnhance(skillEnhance);

	(skillEnhance[5]) ? healMaxTime = 10.0f : healMaxTime = 20.0f;
		

	CreateCollider(D3DXVECTOR2(-60, 0), D3DXVECTOR2(60, 300), L"player", D3DCOLOR_ARGB(255, 0, 255, 0));

	SetState(PlayerIdle::GetInstance());

	nowScene->obm.AddObject(new PlayerUI(this));
}

void Player::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown(VK_LBUTTON))
		std::cout << int(Input::GetInstance().mousePos.x + pos.x) << "   " << Input::GetInstance().mousePos.y << std::endl;

	if (Input::GetInstance().KeyDown('G'))
		Hit(10, D3DXVECTOR2(0, 0));

	if (Input::GetInstance().KeyDown('H'))
		nowScene->obm.AddObject(new Boss2());

	if (!stop)
	{
		CameraControll();
		Combo(deltaTime);
		CancleUpdate(deltaTime);

		if (nowState)
			nowState->UpdateState(this, deltaTime);
	}

	Unit::Update(deltaTime);
}

void Player::Render()
{
	ri.pos = pos;
	shadow.Render(RenderInfo{ D3DXVECTOR2(pos.x, groundPos) });

	if (superAromor)
		outlineShader->Render(outlineShader, GetNowSprite(), ri);
	else
		GetNowSprite().Render(ri);

	Object::Render();
}

void Player::OnCollision(Collider & coli)
{
	if (coli.tag == L"enemybullet")
	{
		if (abs(groundPos - coli.obj->groundPos) >= 100) return;

		auto pBullet = static_cast<Bullet*>(coli.obj);
		Hit(pBullet->damage, pBullet->attackVec);
	}
}

void Player::SetImages()
{
	Resize(Images::END);

	std::wstring path = L"Assets/Sprites/Unit/player/";

	GetSprite(Images::IDLE).LoadAll(path + L"Idle", 0.05f, true);
	GetSprite(Images::MOVE).LoadAll(path + L"Move", 0.03f, true);
	GetSprite(Images::JUMP).LoadAll(path + L"jump", 0.05f, false);
	GetSprite(Images::FALL).LoadAll(path + L"fall", 0.05f, false);
	GetSprite(Images::LANDING).LoadAll(path + L"landing", 0.05f, false);
	GetSprite(Images::HIT).LoadAll(path + L"hit", 0.05f, false);
	GetSprite(Images::STUN).LoadAll(path + L"stun", 0.05f, false);
	GetSprite(Images::STANDUP).LoadAll(path + L"STANDUP", 0.05f, false);
	GetSprite(Images::DIE).LoadAll(path + L"DIE", 0.05f, false);

	GetSprite(Images::JUMPATTACK1).LoadAll(path + L"JUMPATTACK1", 0.05f, false);
	GetSprite(Images::JUMPATTACK2).LoadAll(path + L"JUMPATTACK2", 0.05f, false);
	GetSprite(Images::JUMPATTACK3).LoadAll(path + L"JUMPATTACK3", 0.05f, false);

	GetSprite(Images::WEAKATTACK1).LoadAll(path + L"WEAKATTACK1", 0.02f, false);
	GetSprite(Images::WEAKATTACK2).LoadAll(path + L"WEAKATTACK2", 0.02f, false);
	GetSprite(Images::WEAKATTACK3).LoadAll(path + L"WEAKATTACK3", 0.02f, false);
	GetSprite(Images::WEAKATTACK4).LoadAll(path + L"WEAKATTACK4", 0.01f, false);
	GetSprite(Images::WEAKATTACKEND).LoadAll(path + L"WEAKATTACKEND", 0.02f, false);

	GetSprite(Images::STRONGATTACK).LoadAll(path + L"strongAttack", 0.05f, false);

	GetSprite(Images::SLIDE).LoadAll(path + L"slide", 0.03f, false);
	GetSprite(Images::GUNKATA).LoadAll(path + L"Skillgunkata", 0.04f, false);
	GetSprite(Images::MOVESHOT).LoadAll(path + L"SkillmoveShoot", 0.03f, false);
	GetSprite(Images::MACHINEGUN).LoadAll(path + L"Skillmachinegun", 0.03f, false);
	GetSprite(Images::SNIPER).LoadAll(path + L"Skillsniper", 0.05f, false);
	GetSprite(Images::NUCLEAR).LoadAll(path + L"Skillnuclear", 0.05f, false);
	GetSprite(Images::GRENADE).LoadAll(path + L"grenade", 0.05f, false);
}

void Player::Hit(float damage, D3DXVECTOR2 attackVec)
{
	if (hit || invincible) return;

	Unit::Hit(damage, attackVec);

	nowScene->obm.AddObject(new Effect(L"Player/Hit3", pos + nowScene->GetRandVec(-100, 100, -100, 100), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));

	if (ability.hp <= 0.0f)
		SetState(PlayerDie::GetInstance());
}

void Player::Combo(float deltaTime)
{
	comboInputTimer += deltaTime;

	if (comboInputTimer >= 0.2f)
	{
		comboInputs.clear();
		comboInputTimer = 0.0f;
	}

	InputComboCheck();
	ComboCheck();
	UpdateEfftive(deltaTime);


	comboInterval += deltaTime;
	if (comboInterval >= 0.5f)
	{
		combo = 0;
		comboInterval = 0.0f;
	}
}

void Player::InputComboCheck()
{
	InputCombo(VK_LEFT, "LE");
	InputCombo(VK_RIGHT, "RI");
	InputCombo(VK_DOWN, "DO");
	InputCombo(VK_UP, "UP");

	InputCombo('X', "X");
	InputCombo('S', "S");
}

void Player::InputCombo(unsigned char c, std::string name)
{
	if (Input::GetInstance().KeyDown(c))
	{
		comboInputs.push_back(name);
		comboInputTimer = 0.0f;
	}
}

void Player::ComboCheck()
{
	specialAttack = false;

	ComboChecking(1, 3, "LE", "LE", "X");
	ComboChecking(1, 3, "RI", "RI", "X");

	ComboChecking(2, 3, "LE", "RI", "X");
	ComboChecking(2, 3, "RI", "LE", "X");

	ComboChecking(3, 3, "DO", "RI", "X");
	ComboChecking(3, 3, "DO", "LE", "X");

	ComboChecking(4, 3, "LE", "LE", "S");
	ComboChecking(4, 3, "RI", "RI", "S");

	ComboChecking(5, 4, "RI", "DO", "LE", "X");
	ComboChecking(5, 4, "LE", "DO", "RI", "X");

	ComboChecking(6, 4, "DO", "DO", "UP", "S");

	if (specialAttack && !jump && !jumpAttack)
	{
 		SetState(PlayerSpecialAttack::GetInstance());
		comboInputs.clear();
	}
}

void Player::ComboChecking(int specialIndex, int inputAmount, ...)
{
	std::vector<std::string> ss;
	va_list ap;

	va_start(ap, inputAmount);
	for (int i = 0; i < inputAmount; ++i)
		ss.push_back(va_arg(ap, char*));
	va_end(ap);

	int size = comboInputs.size();

	if (size >= inputAmount)
	{
		int cnt = 0;
		for (int i = 0; i < inputAmount; ++i)
		{
			if (comboInputs[size - i - 1] == ss[inputAmount - i - 1])
				cnt++;
		}
			
		if (cnt == inputAmount)
		{
			this->specialIndex = specialIndex;
			specialAttack = true;
		}
	}
}

void Player::SetSpecialAttack(Images image, float atkScene, float afterImageTime, float mp)
{
	SetAni(image);

	if (this->mp < mp)
	{
		SetState(PlayerIdle::GetInstance());
		return;
	}

	this->mp -= mp;

	if (this->mp <= 0.0f)
		this->mp = 0.0f;

	attackTime = atkScene * GetNowSprite().aniMaxTime;

	if (image == Images::WEAKATTACK4)
	{
		SoundManager::GetInstance().Play("AirShootVoi");
	}
	else if (image == Images::SLIDE)
	{
		SoundManager::GetInstance().Play("Slide");
		SoundManager::GetInstance().Play("SlideVoi");
		force.x += 300 * ri.scale.x;
		nowScene->obm.AddObject(new AttackCollider(team, &pos, D3DXVECTOR2(ri.scale.x * 150, 0), D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 50), 5, D3DXVECTOR2(200, 1000), 1.0f, groundPos, attackTime));
	}
	else if (image == Images::GUNKATA)
	{
		SoundManager::GetInstance().Play("GunKataVoi");

		if (skillEnhance[1])
		{
			nowScene->obm.AddObject(new Effect(L"Player/fire_gunkata2", pos + D3DXVECTOR2(0, 240), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5f), 1, true, GetNowSprite().aniMaxTime));
			nowScene->obm.AddObject(new AttackCollider(team, pos, D3DXVECTOR2(0, 0), D3DXVECTOR2(-400, 0), D3DXVECTOR2(400, 300), 5, D3DXVECTOR2(2, 0), 0.1f, groundPos, attackTime));
		}
		else
		{
			nowScene->obm.AddObject(new Effect(L"Player/fire_gunkata", pos + D3DXVECTOR2(0, 240), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5f), 1, true, GetNowSprite().aniMaxTime));
			nowScene->obm.AddObject(new AttackCollider(team, pos, D3DXVECTOR2(0, 0), D3DXVECTOR2(-400, 0), D3DXVECTOR2(400, 300), 3, D3DXVECTOR2(2, 0), 0.1f, groundPos, attackTime));
		}

		nowScene->obm.AddObject(new SkillEffect(1, attackTime));
		nowScene->obm.AddObject(new AfterImage(0, GetNowSprite(), ri, &pos, layer - 1));
	}
	else if (image == Images::MOVESHOT)
	{
		SoundManager::GetInstance().Play("MoveShotVoi");
		nowScene->obm.AddObject(new AfterImage(4, GetNowSprite(), ri, &pos, layer - 1));
	}
	else if (image == Images::MACHINEGUN)
	{
		SoundManager::GetInstance().Play("MachineVoi");
		nowScene->obm.AddObject(new AfterImage(7, GetNowSprite(), ri, &pos, layer - 1));
	}
	else if (image == Images::SNIPER)
	{
		nowScene->obm.AddObject(new SkillEffect(1, attackTime));
		nowScene->obm.AddObject(new AfterImage(7, GetNowSprite(), ri, &pos, layer - 1));

		SoundManager::GetInstance().Play("SniperReady");
		SoundManager::GetInstance().Play("SniperVoi");
	}
	else if (image == Images::NUCLEAR)
	{
		SoundManager::GetInstance().Play("NuclearVoi");

		bCollider = false;
		nuclear = true;
		nuclearTime = 1.5f;

		nowScene->obm.AddObject(new SkillEffect(3, attackTime));
		nowScene->obm.AddObject(new AfterImage(0, GetNowSprite(), ri, &pos, layer - 1));
		nowScene->obm.AddObject(new Nuclear(pos + D3DXVECTOR2(ri.scale.x * 500, 0)));

		SoundManager::GetInstance().Play("NuclearReady");
	}

	if (afterImageTime > 0.0f)
	{
		this->afterImageTime = afterImageTime;
		afterImage = true;
	}
}

void Player::SetCancel()
{
	if (renderNum == IntEnum(Player::Images::WEAKATTACK4))
	{
		cancel = true;
	}
	else if (renderNum == IntEnum(Player::Images::GUNKATA))
	{
		nowScene->obm.AddObject(new Spectrum(2, GetNowSprite(), ri, layer - 1, attackTime, attackTimer));
		cancel = true;
	}
	else if (renderNum == IntEnum(Player::Images::MACHINEGUN))
	{
		nowScene->obm.AddObject(new Spectrum(4, GetNowSprite(), ri, layer - 1, attackTime, attackTimer));
		cancel = true;
	}

	attackTimer = 0.0f;

	if (cancel)
	{
		Time::GetInstance().timeScale = 0.3f;
		cancel = true;
		cancelTime = 0.2f;
	}
}

void Player::CancleUpdate(float deltaTime)
{
	if (cancel)
	{
		cancelTime -= deltaTime;

		if (cancelTime <= 0.0f)
		{
			cancel = false;
			Time::GetInstance().timeScale = 1.0f;
		}
	}
}

void Player::PlusHp(int value)
{
	ability.hp += value;

	if (ability.hp >= ability.maxHp)
		ability.hp = ability.maxHp;
}

void Player::PlusMp(int value)
{
	mp += value;

	if (mp >= maxMp)
		mp = maxMp;
}

void Player::PlusCombo(int n)
{
	prevCombo = combo;
	combo += n;
	comboInterval = 0.0f;

	if (combo > maxCombo)
		maxCombo = combo;
}

void Player::GetItem(int index)
{
	switch (index)
	{
	case 1:
		powerUp = true;
		powerUpTime = 5.0f;
		break;
	case 2:
		grenade = true;
		break;
	}
}

void Player::UpdateEfftive(float deltaTime)
{
	if (powerUp)
	{
		powerUpTime -= deltaTime;

		if (powerUpTime <= 0.0f)
			powerUp = false;
	}

	if (healTime <= healMaxTime)
		healTime += deltaTime;
	else
	{
		if(Input::GetInstance().KeyDown('D'))
		{
			SoundManager::GetInstance().Play("Heal");
			PlusHp(10.0f);
			healTime = 0.0f;
		}
	}
}

void Player::CreateBullet(D3DXVECTOR2 offset,float damage, float speed, Bullet::Type type, bool jumpshot)
{
	offset.x *= ri.scale.x;

	if (type == Bullet::Type::BASIC)
	{
		Camera::GetInstance().cameraQuaken = { 5, 5 };
		if(jumpshot)
			nowScene->obm.AddObject(new Effect(L"Player/fire_jump", pos + offset, D3DXVECTOR2(ri.scale.x, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));
		else
			nowScene->obm.AddObject(new Effect(L"Player/fire1", pos + offset, D3DXVECTOR2(ri.scale.x, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));

		SoundManager::GetInstance().Play("Basic");
	}
	else if (type == Bullet::Type::AIRSHOT || type == Bullet::Type::MACHINEGUN)
	{
		Camera::GetInstance().cameraQuaken = { 8, 8 };
		nowScene->obm.AddObject(new Effect(L"Player/fire1", pos + offset, D3DXVECTOR2(ri.scale.x, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));

		if(type == Bullet::Type::AIRSHOT)
			SoundManager::GetInstance().Play("Airshot");
		else 
			SoundManager::GetInstance().Play("Machine");
	}
	else if (type == Bullet::Type::SNIPER)
	{
		Camera::GetInstance().cameraQuaken = { 15, 15 };

		nowScene->obm.AddObject(new Effect(L"Player/fire_sniper", pos + offset, D3DXVECTOR2(ri.scale.x, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.07f));

		SoundManager::GetInstance().Play("Sniper");
	}

	offset.y += 20;

	nowScene->obm.AddObject(new Bullet(team, pos + offset, D3DXVECTOR2(ri.scale.x, (jumpshot) ? -1 : 0), damage, speed, type, groundPos));
}

void Player::CameraControll()
{
	if (fallowCamera)
	{
		if(pos.x > -1024 && pos.x < 16800)
			Camera::GetInstance().destCameraPos.x = pos.x;
	}
}

bool Player::Move(float deltaTime, bool moveShot)
{
	D3DXVECTOR2 dir = { 0, 0 };

	if (Input::GetInstance().KeyPress(VK_LEFT))
		dir.x = -1;
	if (Input::GetInstance().KeyPress(VK_RIGHT))
		dir.x = 1;
	if (Input::GetInstance().KeyPress(VK_DOWN))
		dir.y = -1;
	if (Input::GetInstance().KeyPress(VK_UP))
		dir.y = 1;

	if (dir.x == 0 && dir.y == 0)
		return false;

	if (dir.x != 0 && !moveShot)
		ri.scale.x = dir.x;

	if (pos.x + dir.x <= -1860)
		pos.x = -1859;

	if (pos.x + dir.x >= 18115)
		pos.x = 18114;

	int maxY = (nowScene->curStage == 1) ? 200 : -50;
	if (groundPos + dir.y >= maxY)
		groundPos = maxY;

	pos.x += dir.x * ability.speed * deltaTime;
	groundPos += dir.y * ability.speed / 2 * deltaTime;

	return true;
}


void Player::SetState(CState<Player>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);
}

