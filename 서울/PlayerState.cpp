#include "DXUT.h"
#include "PlayerState.h"

PlayerIdle * PlayerIdle::GetInstance()
{
	static PlayerIdle instance;
	return &instance;
}

void PlayerIdle::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::IDLE);
}

void PlayerIdle::UpdateState(Player * obj, float deltaTime)
{
	if (obj->hit)
	{
		obj->SetState(PlayerHit::GetInstance());
		return;
	}

	if (obj->Move(deltaTime))
	{
		obj->SetState(PlayerMove::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('C'))
	{
		obj->SetState(PlayerJump::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('X'))
	{
		obj->SetState(PlayerWeakAttack::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('S'))
	{
		obj->SetState(PlayerStrongAttack::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('F') && obj->grenade)
	{
		obj->SetState(PlayerGrenade::GetInstance());
		return;
	}
}

void PlayerIdle::ExitState(Player * obj)
{
}

PlayerMove * PlayerMove::GetInstance()
{
	static PlayerMove instance;
	return &instance;
}

void PlayerMove::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::MOVE);
	SoundManager::GetInstance().Play("Walk", true);
}

void PlayerMove::UpdateState(Player * obj, float deltaTime)
{
	if (obj->hit)
	{
		obj->SetState(PlayerHit::GetInstance());
		return;
	}

	if (!obj->Move(deltaTime))
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('C'))
	{
		obj->SetState(PlayerJump::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('X'))
	{
		obj->SetState(PlayerWeakAttack::GetInstance());
		return;
	}


	if (Input::GetInstance().KeyDown('S'))
	{
		obj->SetState(PlayerStrongAttack::GetInstance());
		return;
	}


	if (Input::GetInstance().KeyDown('F') && obj->grenade)
	{
		obj->SetState(PlayerGrenade::GetInstance());
		return;
	}
}

void PlayerMove::ExitState(Player * obj)
{
	SoundManager::GetInstance().Stop("Walk");
}

PlayerJump * PlayerJump::GetInstance()
{
	static PlayerJump instance;
	return &instance;
}

void PlayerJump::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::JUMP);

	obj->velocity.y = 1200;
	obj->jump = true;

	SoundManager::GetInstance().Play("JumpVoi");
}

void PlayerJump::UpdateState(Player * obj, float deltaTime)
{
	if (obj->hit)
	{
		obj->SetState(PlayerHit::GetInstance());
		return;
	}

	if (obj->velocity.y <= 0.0f)
	{
		obj->SetState(PlayerFall::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('X') && !obj->jumpAttack)
	{
		obj->SetState(PlayerJumpAttack::GetInstance());
		return;
	}

	obj->Move(deltaTime);
}

void PlayerJump::ExitState(Player * obj)
{
}

PlayerFall * PlayerFall::GetInstance()
{
	static PlayerFall instance;
	return &instance;
}

void PlayerFall::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::FALL);
}

void PlayerFall::UpdateState(Player * obj, float deltaTime)
{
	if (obj->hit)
	{
		obj->SetState(PlayerHit::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyPress('C'))
		obj->velocity.y -= 200;

	if (obj->bGround)
	{
		obj->SetState(PlayerLanding::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('X') && !obj->jumpAttack)
	{
		obj->SetState(PlayerJumpAttack::GetInstance());
		return;
	}

	obj->Move(deltaTime);
}

void PlayerFall::ExitState(Player * obj)
{
}

PlayerLanding * PlayerLanding::GetInstance()
{
	static PlayerLanding instance;
	return &instance;
}

void PlayerLanding::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::LANDING);
}

void PlayerLanding::UpdateState(Player * obj, float deltaTime)
{
	if (Input::GetInstance().KeyPress('C'))
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}

	if (obj->hit)
	{
		obj->SetState(PlayerHit::GetInstance());
		return;
	}

	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}
}

void PlayerLanding::ExitState(Player * obj)
{
	obj->jump = false;
	obj->jumpAttack = false;
}

PlayerHit * PlayerHit::GetInstance()
{
	static PlayerHit instance;
	return &instance;
}

void PlayerHit::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::HIT);
	SoundManager::GetInstance().Play("Hit" + std::to_string(nowScene->GetRandNum(1, 3)));
}

void PlayerHit::UpdateState(Player * obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(PlayerDie::GetInstance());
		return;
	}

	if (obj->velocity.y >= 10)
	{
		obj->SetState(PlayerStun::GetInstance());
		return;
	}

	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}
}

void PlayerHit::ExitState(Player * obj)
{
	obj->hit = false;
}

PlayerStun * PlayerStun::GetInstance()
{
	static PlayerStun instance;
	return &instance;
}

void PlayerStun::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::STUN);
	Camera::GetInstance().cameraQuaken = { 10, 10 };
	obj->bCollider = false;
	obj->jump = true;
	timer = 0.0f;
}

void PlayerStun::UpdateState(Player * obj, float deltaTime)
{
	timer += deltaTime;

	if (Input::GetInstance().KeyDown('C') || timer >= 1.5f)
	{
		obj->SetState(PlayerStandUp::GetInstance());
		return;
	}
}

void PlayerStun::ExitState(Player * obj)
{
}

PlayerStandUp * PlayerStandUp::GetInstance()
{
	static PlayerStandUp instance;
	return &instance;
}

void PlayerStandUp::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::STANDUP);
}

void PlayerStandUp::UpdateState(Player * obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}
}

void PlayerStandUp::ExitState(Player * obj)
{
	obj->bCollider = true;
	obj->jump = false;
	obj->jumpAttack = false;
}

PlayerDie * PlayerDie::GetInstance()
{
	static PlayerDie instance;
	return &instance;
}

void PlayerDie::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::DIE);
	SoundManager::GetInstance().Play("Die");

	timer = 0.0f;
	drawFail = false;
	Time::GetInstance().timeScale = 0.1f;
	Camera::GetInstance().destCameraScale = { 1.5, 1.5 };

	obj->force.x += -obj->ri.scale.x * 70;
	obj->velocity.y = 300;

	obj->bCollider = false;
}

void PlayerDie::UpdateState(Player * obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation && !drawFail)
	{
		drawFail = true;
		nowScene->obm.AddObject(new StageFont(StageFont::Type::FAIL));
	}

	timer += Time::GetInstance().unscaleTime;
	if (timer >= 3.0f)
	{
		Camera::GetInstance().destCameraScale = { 1, 1 };
		Time::GetInstance().timeScale = 1.0f;
	}
}

void PlayerDie::ExitState(Player * obj)
{
}

PlayerJumpAttack * PlayerJumpAttack::GetInstance()
{
	static PlayerJumpAttack instance;
	return &instance;
}

void PlayerJumpAttack::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::JUMPATTACK1);

	combo = 0;
	comboInput = 0;
	timer = 0;

	obj->gravity = 3.0f;
	obj->velocity.y = 0.0f;
	obj->jumpAttack = true;
}

void PlayerJumpAttack::UpdateState(Player * obj, float deltaTime)
{
	if (obj->hit)
	{
		obj->SetState(PlayerStun::GetInstance());
		return;
	}

	if (obj->bGround)
	{
		obj->SetState(PlayerLanding::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('X'))
	{
		if (comboInput < 3)
			comboInput++;
	}

	if (obj->GetNowSprite().scene == 0 && !obj->onAttack)
	{
		obj->onAttack = true;
		obj->CreateBullet(D3DXVECTOR2(170, 150), 5, 1000, Bullet::Type::BASIC, true);
	}

	if (!obj->GetNowSprite().bAnimation && combo < comboInput)
	{
		combo++;
		obj->onAttack = false;
		timer = 0.0f;

		if (combo == 3)
		{
			obj->SetState(PlayerFall::GetInstance());
			return;
		}

		obj->SetAni(PlusEnum(Player::Images, Player::Images::JUMPATTACK1, combo));
	}

	if (timer >= 0.2f && !obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerFall::GetInstance());
		return;
	}

	obj->Move(deltaTime, true);

	timer += deltaTime;
}

void PlayerJumpAttack::ExitState(Player * obj)
{
	obj->gravity = 9.8f;
	obj->onAttack = false;
}

PlayerWeakAttack * PlayerWeakAttack::GetInstance()
{
	static PlayerWeakAttack instance;
	return &instance;
}

void PlayerWeakAttack::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::WEAKATTACK1);

	combo = 0;
	comboInput = 0;
	timer = 0;
}

void PlayerWeakAttack::UpdateState(Player * obj, float deltaTime)
{
	if (obj->hit)
	{
		obj->SetState(PlayerHit::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('X'))
	{
		if (comboInput < 3)
			comboInput++;
	}

	if (obj->GetSprite(Player::Images::WEAKATTACK1).scene == 4 && !obj->onAttack)
	{
		obj->CreateBullet(D3DXVECTOR2(250, 210), 5, 1500, Bullet::Type::BASIC);
		obj->onAttack = true;
	}
	else if (obj->renderNum != IntEnum(Player::Images::WEAKATTACK1) && obj->GetNowSprite().scene == 2 && !obj->onAttack)
	{
		obj->CreateBullet(D3DXVECTOR2(250, 210), 5, 1500, Bullet::Type::BASIC);
		obj->onAttack = true;
	}

	if (!obj->GetNowSprite().bAnimation && combo < comboInput)
	{
		combo++;
		obj->onAttack = false;
		timer = 0.0f;

		if (combo == 3)
		{
			obj->specialIndex = 0;
			obj->SetState(PlayerSpecialAttack::GetInstance());
			return;
		}

		obj->SetAni(PlusEnum(Player::Images, Player::Images::WEAKATTACK1, combo));
	}

	if (timer >= 0.2f && !obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerWeakAttackEnd::GetInstance());
		return;
	}

	timer += deltaTime;
}

void PlayerWeakAttack::ExitState(Player * obj)
{
	obj->onAttack = false;
}

PlayerWeakAttackEnd * PlayerWeakAttackEnd::GetInstance()
{
	static PlayerWeakAttackEnd instance;
	return &instance;
}

void PlayerWeakAttackEnd::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::WEAKATTACKEND);
}

void PlayerWeakAttackEnd::UpdateState(Player * obj, float deltaTime)
{
	if (obj->hit)
	{
		obj->SetState(PlayerHit::GetInstance());
		return;
	}

	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}
}

void PlayerWeakAttackEnd::ExitState(Player * obj)
{
}


PlayerStrongAttack * PlayerStrongAttack::GetInstance()
{
	static PlayerStrongAttack instance;
	return &instance;
}

void PlayerStrongAttack::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::STRONGATTACK);
	obj->specialIndex = -1;
	obj->superAromor = true;
	SoundManager::GetInstance().Play("Kick");
}

void PlayerStrongAttack::UpdateState(Player * obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(PlayerDie::GetInstance());
		return;
	}

	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}

	if (obj->GetNowSprite().scene == 3 && !obj->onAttack)
	{
		obj->onAttack = true;
		nowScene->obm.AddObject(new AttackCollider(obj->team, obj->pos, D3DXVECTOR2(obj->ri.scale.x * 100, 0), D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 250), 10, D3DXVECTOR2(200, 0), 0.0f, obj->groundPos, 0.1f));
	}
}

void PlayerStrongAttack::ExitState(Player * obj)
{
	obj->onAttack = false;
	obj->superAromor = false;
}



PlayerSpecialAttack * PlayerSpecialAttack::GetInstance()
{
	static PlayerSpecialAttack instance;
	return &instance;
}

void PlayerSpecialAttack::EnterState(Player * obj)
{
	obj->SetCancel();
	obj->superAromor = true;

	if (obj->specialIndex == 0) obj->SetSpecialAttack(Player::Images::WEAKATTACK4, 9, 0.0f, 0);
	else if (obj->specialIndex == 1) obj->SetSpecialAttack(Player::Images::SLIDE, 9, 0.0f, 10);
	else if (obj->specialIndex == 2) obj->SetSpecialAttack(Player::Images::GUNKATA, 23, 0.15f, 20);
	else if (obj->specialIndex == 3) obj->SetSpecialAttack(Player::Images::MOVESHOT, 2, 0.15f, 15);
	else if (obj->specialIndex == 4) obj->SetSpecialAttack(Player::Images::MACHINEGUN, 3, 0.0f, 20);
	else if (obj->specialIndex == 5) obj->SetSpecialAttack(Player::Images::SNIPER, 9, 0.15f, 30);
	else if (obj->specialIndex == 6) obj->SetSpecialAttack(Player::Images::NUCLEAR, 0, 0.15f, 30);
}

void PlayerSpecialAttack::UpdateState(Player * obj, float deltaTime)
{
	obj->attackTimer += deltaTime;

	if (obj->ability.hp <= 0)
	{
		obj->SetState(PlayerDie::GetInstance());
		return;
	}

	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}

	if (obj->specialIndex == 0)
	{
		if (obj->attackTimer >= obj->attackTime && !obj->onAttack)
		{
			obj->CreateBullet(D3DXVECTOR2(250, 200), 10, 1500, Bullet::Type::AIRSHOT);
			obj->onAttack = true;
		}

		if (obj->onAttack)
		{
			if (Input::GetInstance().KeyDown('C'))
			{
				obj->SetCancel();

				obj->SetState(PlayerJump::GetInstance());
				return;
			}
		}
	}
	else if (obj->specialIndex == 2)
	{
		Camera::GetInstance().cameraQuaken = { 2, 2 };
	}
	else if (obj->specialIndex == 3)
	{
		if ((obj->GetNowSprite().scene > 2 && obj->GetNowSprite().scene < 14) ||
			obj->GetNowSprite().scene > 19 && obj->GetNowSprite().scene < 33)
		{
			if (obj->attackTimer >= obj->attackTime)
			{

				static bool change = false;
				D3DXVECTOR2 offset = { 230, 250 };

				(change) ? offset.y += 10 : offset.y -= 10;

				if (obj->skillEnhance[2])
					obj->CreateBullet(offset, 8, 1500, Bullet::Type::MACHINEGUN);
				else
					obj->CreateBullet(offset, 5, 1500, Bullet::Type::BASIC);

				obj->attackTimer = 0.0f;

				change = !change;
			}
		}

		obj->Move(deltaTime, true);
	}
	else if (obj->specialIndex == 4)
	{
		if (obj->GetNowSprite().scene > 8)
		{
			if (obj->attackTimer >= obj->attackTime)
			{
				if(obj->skillEnhance[3])
					obj->CreateBullet(D3DXVECTOR2(250, 200), 12, 2000, Bullet::Type::EMACHINEGUN);
				else
					obj->CreateBullet(D3DXVECTOR2(250, 200), 8, 2000, Bullet::Type::MACHINEGUN);

				obj->attackTimer = 0.0f;
			}
		}
	}
	else if (obj->specialIndex == 5)
	{
		if (obj->attackTimer >= obj->attackTime && !obj->onAttack)
		{
			obj->onAttack = true;

			if(obj->skillEnhance[4])
				obj->CreateBullet(D3DXVECTOR2(250, 200), 30, 3000, Bullet::Type::SNIPER);
			else
				obj->CreateBullet(D3DXVECTOR2(250, 200), 60, 3000, Bullet::Type::ESNIPER);
		}
	}
	else if (obj->specialIndex == 6)
	{
		obj->nuclearTime -= deltaTime;

		if (obj->GetNowSprite().scene == 11 && !obj->onAttack)
			obj->GetNowSprite().bAniStop = true;

		if (Input::GetInstance().keyUp('S') || obj->nuclearTime <= 0.0f)
		{
			if (!obj->onAttack)
			{
				obj->onAttack = true;

				SoundManager::GetInstance().Play("NuclearReady2");
				SoundManager::GetInstance().Play("NuclearFall");
				SoundManager::GetInstance().Play("NuclearSound");

				obj->bCollider = true;
				obj->nuclear = false;
				obj->GetNowSprite().bAniStop = false;

			}
		}
	}

	if (obj->afterImage)
	{
		obj->afterImageTimer += deltaTime;

		if (obj->afterImageTimer >= obj->afterImageTime)
		{
			nowScene->obm.AddObject(new AfterImage(obj->GetNowSprite(), obj->ri, D3DCOLOR_ARGB(70, 0, 0, 0), 0.5f, obj->layer - 1));
			obj->afterImageTimer = 0.0f;
		}
	}
}

void PlayerSpecialAttack::ExitState(Player * obj)
{
	obj->onAttack = false;
	obj->afterImage = false;
	obj->afterImageTimer = 0.0f;
	obj->superAromor = false;
}

PlayerGrenade * PlayerGrenade::GetInstance()
{
	static PlayerGrenade instance;
	return &instance;
}

void PlayerGrenade::EnterState(Player * obj)
{
	obj->SetAni(Player::Images::GRENADE);
	obj->grenade = false;
	
}

void PlayerGrenade::UpdateState(Player * obj, float deltaTime)
{
	if (obj->GetNowSprite().scene == 3 && !obj->onAttack)
	{
		obj->onAttack = true;
		nowScene->obm.AddObject(new Bullet(obj->team, obj->pos + D3DXVECTOR2(obj->ri.scale.x * 100, 150), D3DXVECTOR2(obj->ri.scale.x, 0.1), 30, 1500, Bullet::Type::GRENADE, obj->groundPos));
		SoundManager::GetInstance().Play("GrenadeVoi");
	}

	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}
}

void PlayerGrenade::ExitState(Player * obj)
{
	obj->onAttack = false;
}
