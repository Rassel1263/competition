#include "DXUT.h"
#include "Unit.h"

Unit::Unit()
{
	ri.pivot = { 0.5, 0.0 };

	shadow.LoadAll(L"Assets/Sprites/effect/shadow");

	SetRigid();
}

void Unit::Update(float deltaTime)
{
	layer = 1080 - (groundPos + 540);

	if (hit)
	{
		hitTimer += deltaTime;

		if (hitTimer >= hitTime)
		{
			hit = false;
			hitTimer = 0.0f;
		}
	}

	GetNowSprite().Update(deltaTime);

	Object::Update(deltaTime);
}

void Unit::Render()
{
	ri.pos = pos;
	GetNowSprite().Render(ri);

	Object::Render();
}

void Unit::OnCollision(Collider & coli)
{
}

void Unit::Hit(float damage, D3DXVECTOR2 attackVec)
{
	hit = true;

	if (!superAromor)
	{
		force.x += attackVec.x;
		velocity.y = attackVec.y;
	}

	ability.hp -= damage;

	SoundManager::GetInstance().Play("Hit");

	if (ability.hp <= 0)
		ability.hp = 0.0f;
}

bool Unit::Blink(float deltaTime, float amount)
{
	static float destColor = -1.0f;
	static int blink = 0;

	GetNowSprite().color.a += deltaTime * destColor * 3;
	 
	if (GetNowSprite().color.a <= 0.0f || GetNowSprite().color.a >= 1.0f)
	{
		GetNowSprite().color.a = std::clamp(GetNowSprite().color.a, 0.0f, 1.0f);

		++blink;
		destColor = -destColor;
	}

	if (GetNowSprite().color.a <= 0.0f && blink >= amount)
		return false;

	return true;
}

bool Unit::DetectRange(Range * range)
{
	if (range->detect)
	{
		range->detect = false;
		return true;
	}
	else
		return false;

}

Sprite & Unit::GetNowSprite()
{
	return sprites[renderNum];
}
