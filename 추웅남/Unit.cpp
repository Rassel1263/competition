#include "DXUT.h"
#include "Unit.h"

Unit::Unit()
{
	colorShader = new ColorShader();
}

void Unit::Update(float deltaTime)
{
	if(hit)
	{
		hitTimer += deltaTime;

		if (hitTimer >= hitTime)
		{
			hitTimer = 0.0f;
			hit = false;
		}
	}

	GetNowSprite().Update(deltaTime);
}

void Unit::Render()
{
	ri.pos = pos;
	GetNowSprite().Render(ri);

	Object::Render();
}

void Unit::Hit(float damage)
{
	hit = true;

	ability.hp -= damage;

	if (ability.hp <= 0)
		ability.hp = 0.0f;
}

void Unit::Move(float deltaTime)
{
}

void Unit::SetRotate(int rotate, int scene)
{
	renderNum = abs(rotate / (360 / scene) % scene);
}
