#include "DXUT.h"

BossIdle * BossIdle::GetInstance()
{
	static BossIdle instance;
	return &instance;
}

void BossIdle::EnterState(CBoss * obj)
{
	obj->SetAni(CBoss::Images::IDLE);
}

void BossIdle::UpdateState(CBoss * obj, float deltaTime)
{
	if (obj->hit && !obj->superAromor)
	{
		obj->SetState(BossHit::GetInstance());
		return;
	}

	if (obj->Move(deltaTime))
	{
		obj->SetState(BossMove::GetInstance());
		return;
	}

	if (obj->pattern == 1)
	{
		obj->SetState(BossPaatern1::GetInstance());
		return;
	}

	if (obj->pattern == 2)
	{
		obj->SetState(BossPaatern2::GetInstance());
		return;
	}

	if (obj->pattern == 3)
	{
		obj->SetState(BossPaatern3::GetInstance());
		return;
	}
}

void BossIdle::ExitState(CBoss * obj)
{
}

BossMove * BossMove::GetInstance()
{
	static BossMove instance;
	return &instance;
}

void BossMove::EnterState(CBoss * obj)
{
	obj->SetAni(CBoss::Images::MOVE);
}

void BossMove::UpdateState(CBoss * obj, float deltaTime)
{
	if (obj->hit && !obj->superAromor)
	{
		obj->SetState(BossHit::GetInstance());
		return;
	}

	if (!obj->Move(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}

	if (obj->pattern == 1)
	{
		obj->SetState(BossPaatern1::GetInstance());
		return;
	}

	if (obj->pattern == 2)
	{
		obj->SetState(BossPaatern2::GetInstance());
		return;
	}

	if (obj->pattern == 3)
	{
		obj->SetState(BossPaatern3::GetInstance());
		return;
	}
}

void BossMove::ExitState(CBoss * obj)
{
}

BossHit * BossHit::GetInstance()
{
	static BossHit instance;
	return &instance;
}

void BossHit::EnterState(CBoss * obj)
{
	obj->SetAni(CBoss::Images::HIT);
}

void BossHit::UpdateState(CBoss * obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(BossDie::GetInstance());
		return;
	}

	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossHit::ExitState(CBoss * obj)
{
	obj->hit = false;
}

BossStun * BossStun::GetInstance()
{
	static BossStun instance;
	return &instance;
}

void BossStun::EnterState(CBoss * obj)
{
}

void BossStun::UpdateState(CBoss * obj, float deltaTime)
{
}

void BossStun::ExitState(CBoss * obj)
{
}

BossDie * BossDie::GetInstance()
{
	static BossDie instance;
	return &instance;

}

void BossDie::EnterState(CBoss * obj)
{
	obj->SetAni(CBoss::Images::DIE);

	Time::GetInstance().timeScale = 0.2f;
	nowScene->player->fallowCamera = false;
	Camera::GetInstance().destCameraPos = obj->pos;
	Camera::GetInstance().destCameraScale = { 1.5 ,1.5 };
	drawClear = false;
	timer = 0.0f;
}

void BossDie::UpdateState(CBoss * obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		Time::GetInstance().timeScale = 1.0f;
		nowScene->player->fallowCamera = true;
		Camera::GetInstance().destCameraPos.y = 0;
		Camera::GetInstance().destCameraScale = { 1 ,1 };

		timer += deltaTime; 

		if (timer >= 1.0f && !drawClear)
		{
			drawClear = true;
			nowScene->obm.AddObject(new StageFont(StageFont::Type::CLEAR));
		}
	}
}

void BossDie::ExitState(CBoss * obj)
{
}

BossPaatern1 * BossPaatern1::GetInstance()
{
	static BossPaatern1 instance;
	return &instance;
}

void BossPaatern1::EnterState(CBoss * obj)
{
	obj->SetAni(CBoss::Images::ATTACK1);
}

void BossPaatern1::UpdateState(CBoss * obj, float deltaTime)
{
	if (obj->hit && !obj->superAromor)
	{
		obj->SetState(BossHit::GetInstance());
		return;
	}

	if (!obj->Pattern1(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossPaatern1::ExitState(CBoss * obj)
{
	obj->ResetPattern();
}

BossPaatern2 * BossPaatern2::GetInstance()
{
	static BossPaatern2 instance;
	return &instance;
}

void BossPaatern2::EnterState(CBoss * obj)
{
	obj->SetAni(CBoss::Images::ATTACK2);
}

void BossPaatern2::UpdateState(CBoss * obj, float deltaTime)
{
	if (obj->hit && !obj->superAromor)
	{
		obj->SetState(BossHit::GetInstance());
		return;
	}

	if (!obj->Pattern2(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossPaatern2::ExitState(CBoss * obj)
{
	obj->ResetPattern();
}

BossPaatern3 * BossPaatern3::GetInstance()
{
	static BossPaatern3 instance;
	return &instance;
}

void BossPaatern3::EnterState(CBoss * obj)
{
	obj->SetAni(CBoss::Images::ATTACK3);
}

void BossPaatern3::UpdateState(CBoss * obj, float deltaTime)
{
	if (obj->hit && !obj->superAromor)
	{
		obj->SetState(BossHit::GetInstance());
		return;
	}

	if (!obj->Pattern3(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossPaatern3::ExitState(CBoss * obj)
{
	obj->ResetPattern();
}
