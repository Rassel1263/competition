#include "DXUT.h"
#include "Player.h"

Player::Player()
{
	team = L"player";

	Resize(24);

	for (int i = 0; i < 24; ++i)
		GetSprite(i).LoadAll(L"Assets/Sprites/player/move/" + std::to_wstring(i), 0.05f, true);

	weapons.push_back(new MachineGun(this));
	weapons.push_back(new NavanGun(this));
	weapons.push_back(new TorpedoLauncher(this));
	weapons.push_back(new MissileLauncher(this));

	ability.SetAbility(100, 75);

	nowScene->miniMap->AddMiniObj(MiniMap::MiniInfo{ MiniTag::PLAYER, this });

	CreateCollider(D3DXVECTOR2(-100, -100), D3DXVECTOR2(100, 100), L"player");
}

void Player::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown('G'))
		nowScene->obm.AddObject(new Item(pos + D3DXVECTOR2(0, 400), nowScene->GetRandNum(0, 5)));

	if (Input::GetInstance().KeyDown('F'))
		Hit(20);

	if (Input::GetInstance().KeyDown('Z'))
		nowScene->enemyManager.SpawnEnemy(pos + D3DXVECTOR2(0, 400), CEnemy::Type::BigFly);

	if (ability.hp <= 0)
	{
		if (!GetNowSprite().bAnimation && !drawGameOver)
		{
			drawGameOver = true;
			nowScene->obm.AddObject(new StageFont(StageFont::Type::FAIL));
		}

		GetNowSprite().Update(Time::GetInstance().unscaleTime);
		return;
	}

	CameraControll(deltaTime);

	if (intro)
	{
		pos.y += deltaTime * 75;
		GetNowSprite().Update(deltaTime);

		return;
	}

	if (!stop)
	{
		Move(deltaTime);
		WeaponControll(deltaTime);
		SkillControll(deltaTime);
		UpdateEffective(deltaTime);
	}

	Unit::Update(deltaTime);
}

void Player::Render()
{
	ri.pos = pos;

	if (god)
		colorShader->Render(colorShader, GetNowSprite(), ri, D3DXVECTOR4(1, 1, 0, 0.5), true);
	else if (speedDown)
		colorShader->Render(colorShader, GetNowSprite(), ri, D3DXVECTOR4(0, 1, 0, 0.5), true);
	else
		GetNowSprite().Render(ri);

	Object::Render();
}

void Player::OnCollision(Collider& coli)
{
	if (god) return;

	if (coli.tag == L"enemy")
	{
		if (static_cast<CEnemy*>(coli.obj)->type == CEnemy::Type::Float)
			Hit(10);
		if (static_cast<CEnemy*>(coli.obj)->type == CEnemy::Type::BigFloat)
		{
			Hit(10);
			pos.y -= 200;
		}
	}

	if (coli.tag == L"enemybullet")
	{
		Hit(static_cast<Bullet*>(coli.obj)->damage);
	}

	if (coli.tag == L"obstacle")
	{
		if (static_cast<Obstacle*>(coli.obj)->type == Obstacle::Type::MINE)
			Hit(15);

		if (static_cast<Obstacle*>(coli.obj)->type == Obstacle::Type::ROCK)
		{
			pos.y -= 200;
			Hit(10);
		}

		GetEffective(6);
	}

	if (coli.tag == L"hitbox")
	{
		Hit(static_cast<HitBox*>(coli.obj)->damage);
	}
}

void Player::Hit(float damage)
{
	if (hit || invincible) return;

	Unit::Hit(damage);
	nowScene->obm.AddObject(new HitEffect());

	nowScene->msgBox->SpawnMsg(L"Hit", 0);

	Camera::GetInstance().cameraQuaken = { 20, 20 };

	if (ability.hp <= 0)
	{
		bCollider = false;
		GetNowSprite().LoadAll(L"Assets/Sprites/player/sink/" + std::to_wstring(renderNum), 0.07f, false);
		fallowCamera = false;
		dps = 0.0f;
		nowScene->stopTime = true;
		Camera::GetInstance().destCameraScale = { 1.5, 1.5 };
		Camera::GetInstance().destCameraPos = pos;
		Time::GetInstance().timeScale = 0.3f;
	}
}

void Player::Move(float deltaTime)
{
	if (Input::GetInstance().KeyDown(VK_UP))
		speedLevel++;

	if (Input::GetInstance().KeyDown(VK_DOWN))
		speedLevel--;

	speedLevel = std::clamp(speedLevel, 1, 4);

	if (Input::GetInstance().KeyPress(VK_LEFT))
		curRotate -= speedLevel * 40 * deltaTime;

	if (Input::GetInstance().KeyPress(VK_RIGHT))
		curRotate += speedLevel * 40 * deltaTime;

	if (curRotate > 360)
		curRotate = 0;
	else if (curRotate < 0)
		curRotate = 360;

	curRadian = D3DXToRadian(-curRotate + 90);

	destSpeed = speedLevel * ((speedUp) ? 150 : 75);
	if (speedDown) destSpeed /= 2;
	ability.speed += std::ceil(destSpeed - ability.speed) * 0.1f;

	prevPos = pos;
	pos += D3DXVECTOR2(cosf(curRadian), sinf(curRadian)) * ability.speed * deltaTime;

	if (nowScene->spawnBoss)
	{
		if (pos.x > Camera::GetInstance().cameraPos.x + 1300 || pos.x < Camera::GetInstance().cameraPos.x - 1300 ||
			pos.y > Camera::GetInstance().cameraPos.y + 700 || pos.y < Camera::GetInstance().cameraPos.y - 700)
			pos = prevPos;

	}
	else
	{
		if (pos.x > limitPos.x || pos.x < -limitPos.x || pos.y < -limitPos.y)
			pos = prevPos;

		dps = pos.y - prevPos.y;
	}

	SetRotate(curRotate, 24);
}

void Player::SetTarget(CEnemy::Type type)
{
	float minLength = INT_MAX;

	target = NULL;

	if (nowScene->enemyManager.allEnemys.size() < 0)
		return;

	if (type == CEnemy::Type::None)
	{
		for (auto& enemy : nowScene->enemyManager.allEnemys)
		{
			if (enemy->pos.x > Camera::GetInstance().cameraPos.x + 960 || enemy->pos.x < Camera::GetInstance().cameraPos.x - 960 ||
				enemy->pos.y > Camera::GetInstance().cameraPos.y + 560 || enemy->pos.y < Camera::GetInstance().cameraPos.y - 560)
				continue;

			float distance = D3DXVec2Length(&(enemy->pos - pos));
			if (distance < minLength)
			{
				minLength = distance;
				target = enemy;
			}
		}
	}

	if (type == CEnemy::Type::Float)
	{
		for (auto& enemy : nowScene->enemyManager.floatEnemys)
		{
			float distance = D3DXVec2Length(&(enemy->pos - pos));
			if (distance < minLength)
			{
				minLength = distance;
				target = enemy;
			}
		}
	}

	if (type == CEnemy::Type::Fly)
	{
		for (auto& enemy : nowScene->enemyManager.flyEnemys)
		{
			if (enemy->pos.x > Camera::GetInstance().cameraPos.x + 960 || enemy->pos.x < Camera::GetInstance().cameraPos.x - 960 ||
				enemy->pos.y > Camera::GetInstance().cameraPos.y + 560 || enemy->pos.y < Camera::GetInstance().cameraPos.y - 560)
				continue;

			float distance = D3DXVec2Length(&(enemy->pos - pos));
			if (distance < minLength)
			{
				minLength = distance;
				target = enemy;
			}
		}
	}

	if (target)
	{
		targitTimer = 1.0f;

		if (target != prevTarget)
		{
			prevTarget = target;
			nowScene->obm.AddObject(new Effect(L"Sniper", target->pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
		}
	}
}

void Player::WeaponControll(float deltaTime)
{
	for (auto& weapon : weapons)
		weapon->Update(deltaTime);

	if (Input::GetInstance().KeyPress('Q'))
	{
		SetTarget(CEnemy::Type::None);

		if (target)
			weapons[0]->Shoot(nowScene->GetAngleFromTarget(pos, target->pos));
		else
			weapons[0]->Shoot(-curRotate + 90 + nowScene->GetRandNum(-15, 15));
	}

	if (Input::GetInstance().KeyDown('W'))
	{
		SetTarget(CEnemy::Type::None);

		if (target)
			weapons[1]->Shoot(nowScene->GetAngleFromTarget(pos, target->pos));
		else
			weapons[1]->Shoot(-curRotate + 90 + nowScene->GetRandNum(-30, 30));
	}

	if (Input::GetInstance().KeyDown('E'))
	{
		SetTarget(CEnemy::Type::Float);

		if (target)
			weapons[2]->Shoot(-curRotate + 90);
	}

	if (Input::GetInstance().KeyDown('R'))
	{
		SetTarget(CEnemy::Type::Fly);

		if (target)
			weapons[3]->Shoot(-curRotate + 90);
	}
}

void Player::CameraControll( float deltaTime)
{
	if (fallowCamera)
	{
		if (target)
		{
			if (target->pos.x > pos.x + 960 || target->pos.x < pos.x - 960 ||
				target->pos.y > pos.y + 560 || target->pos.y < pos.y - 560)
			{
				target = NULL;
			}
			else if (targitTimer <= 0.0f)
			{
				targitTimer = 0.0f;
				target = NULL;
			}
			else
			{
				Camera::GetInstance().destCameraPos = target->pos;
				targitTimer -= deltaTime;
			}
		}
		else
		{
			if (pos.x > -2000 && pos.x < 2000)
				Camera::GetInstance().destCameraPos = D3DXVECTOR2(pos.x, pos.y + 200);
		}
	}
}

void Player::SkillControll(float deltaTime)
{
	if (Input::GetInstance().KeyDown('A'))
	{
		if (skill1CoolTimer <= 0.0f && !skill1)
		{
			skill1 = true;
			skill1Timer = 5.0f;
			weapons[0]->shootInterval /= 4;

			nowScene->obm.AddObject(new FocusSKill());
		}
		else
			nowScene->msgBox->SpawnMsg(L"obtainSkill", 1);
	}

	if (Input::GetInstance().KeyDown('S'))
	{
		if (skill2CoolTimer <= 0.0f)
		{
			skill2CoolTimer = skill2CoolTime;
			nowScene->obm.AddObject(new Airsupport());
		}
		else
			nowScene->msgBox->SpawnMsg(L"obtainSkill", 1);


	}

	if (skill1)
	{
		skill1Timer -= deltaTime;

		if (skill1Timer <= 0.0f)
		{
			skill1 = false;
			weapons[0]->shootInterval *= 4;
			skill1CoolTimer = skill1CoolTime;
		}
	}

	if (skill1CoolTimer > 0.0f)
		skill1CoolTimer -= deltaTime;

	if (skill2CoolTimer > 0.0f)
		skill2CoolTimer -= deltaTime;

}

void Player::GetEffective(int index)
{
	switch (index)
	{
	case 0:
		weapons[0]->bulletAmount += 30;
		if (weapons[0]->bulletAmount >= 150)
			weapons[0]->bulletAmount = 150;

		nowScene->msgBox->SpawnMsg(L"obtainMachinegun", 0);
		break;
	case 1:
		weapons[1]->bulletAmount += 5;

		if (weapons[1]->bulletAmount >= weapons[1]->bulletMaxAmout)
			weapons[1]->bulletAmount = weapons[1]->bulletMaxAmout;

		nowScene->msgBox->SpawnMsg(L"obtainTorpedo", 0);
		break;
	case 2:
		weapons[2]->bulletAmount += 3;

		if (weapons[2]->bulletAmount >= weapons[2]->bulletMaxAmout)
			weapons[2]->bulletAmount = weapons[2]->bulletMaxAmout;

		nowScene->msgBox->SpawnMsg(L"MissileReady", 0);
		break;
	case 3:
		speedUp = true;
		speedUpTime = 5.0f;

		nowScene->msgBox->SpawnMsg(L"obtainBooster", 0);
		break;
	case 4:
		invincible = true;
		invincibleTime = 2.0f;

		nowScene->msgBox->SpawnMsg(L"obtainEventbox", 0);
		break;
	case 5:
		ability.hp += 20;

		if (ability.hp >= ability.maxHp)
			ability.hp = ability.maxHp;

		nowScene->msgBox->SpawnMsg(L"obtainToolbox", 0);
		break;
	case 6:
		speedDown = true;
		speedDownTime = 2.0f;
		break;
	}
}

void Player::UpdateEffective(float deltaTime)
{
	if (speedUp)
	{
		speedUpTime -= deltaTime;

		if (speedUpTime <= 0.0f)
			speedUp = false;
	}

	if (speedDown)
	{
		speedDownTime -= deltaTime;

		if (speedDownTime <= 0.0f)
			speedDown = false;
	}

	if (invincible)
	{
		invincibleTime -= deltaTime;

		if (invincibleTime <= 0.0f)
			invincible = false;
	}
}

