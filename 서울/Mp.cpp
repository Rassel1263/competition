#include "DXUT.h"
#include "Mp.h"

Mp::Mp(D3DXVECTOR2 pos, float amount)
{
	this->pos = pos;
	this->amount = amount;

	if(amount < 5)
		spr.LoadAll(L"Assets/Sprites/effect/Player/Mp/1", 0.05f, false);
	else
		spr.LoadAll(L"Assets/Sprites/effect/Player/Mp/2", 0.05f, false);

	angle = D3DXToRadian(nowScene->GetRandNum(0, 360));
	turnSpeed = D3DXToRadian(10);

	CreateCollider(D3DXVECTOR2(-5, -5), D3DXVECTOR2(5, 5), L"mp");
}

void Mp::Update(float deltaTime)
{
	if (hit)
	{
		if (!spr.bAnimation)
			destroy = true;

		spr.Update(deltaTime);
	}

	turnTime += deltaTime;

	if (turnTime >= 0.01f)
	{
		D3DXVECTOR2 distance = nowScene->player->pos + D3DXVECTOR2(0, 150) - pos;
		float targetAngle = atan2(distance.y, distance.x);
		float diff = targetAngle - angle;

		if (diff > D3DX_PI)
			diff -= D3DX_PI * 2;
		else if (diff < -D3DX_PI)
			diff += D3DX_PI * 2;

		if (diff > turnSpeed)
			angle += turnSpeed;
		else if (diff < -turnSpeed)
			angle -= turnSpeed;
		else
			angle = targetAngle;

		turnTime = 0.0f;
	}

	pos += D3DXVECTOR2(cosf(angle), sinf(angle)) * 1000 * deltaTime;
}

void Mp::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}

void Mp::OnCollision(Collider & coli)
{
	if (coli.tag == L"player")
	{
		if (!hit)
		{
			nowScene->player->PlusMp(amount);
			hit = true;
		}
	}
}
