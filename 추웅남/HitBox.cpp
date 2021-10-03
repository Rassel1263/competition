#include "DXUT.h"
#include "HitBox.h"

HitBox::HitBox(D3DXVECTOR2 pos, D3DXVECTOR2 min, D3DXVECTOR2 max, float damage, float time)
{
	this->pos = pos;
	this->damage = damage;
	this->timer = time;
	CreateCollider(min, max, L"hitbox");
}

void HitBox::Update(float deltaTime)
{
	timer -= deltaTime;

	if (timer <= 0.0f)
		destroy = true;
}

void HitBox::Render()
{
	Object::Render();
}
