#include "DXUT.h"
#include "AttackCollider.h"

AttackCollider::AttackCollider(std::wstring tag, D3DXVECTOR2 pos, D3DXVECTOR2 offset, D3DXVECTOR2 min, D3DXVECTOR2 max, float damage, D3DXVECTOR2 attackVec, float yVec, float groundPos, float time)
{
	this->tag = tag;
	this->ownerPos = pos;
	this->pos = pos + offset;
	this->damage = damage;
	this->attackVec = attackVec;
	this->yVec = yVec;
	this->groundPos = groundPos;
	this->time = time;

	CreateCollider(min, max, tag + L"atk");
}

AttackCollider::AttackCollider(std::wstring tag, D3DXVECTOR2 * pos, D3DXVECTOR2 offset, D3DXVECTOR2 min, D3DXVECTOR2 max, float damage, D3DXVECTOR2 attackVec, float yVec, float groundPos, float time)
{
	this->tag = tag;
	this->ownerPos = *pos;
	this->fallowPos = pos;
	this->damage = damage;
	this->attackVec = attackVec;
	this->yVec = yVec;
	this->groundPos = groundPos;
	this->time = time;

	CreateCollider(min, max, tag + L"atk");
}

void AttackCollider::Update(float deltaTime)
{
	time -= deltaTime;

	if (time <= 0)
		destroy = true;

	if (fallowPos)
	{
		ownerPos = pos;
		pos = *fallowPos + offset;
	}
}

void AttackCollider::Render()
{
	Object::Render();
}

void AttackCollider::OnCollision(Collider & coli)
{
	if (coli.tag == tag) return;

	if (coli.tag == L"player" || coli.tag == L"enemy")
	{
		if (abs(groundPos - coli.obj->groundPos) >= 100) return;
		
		D3DXVECTOR2 dir = { (ownerPos.x - coli.obj->pos.x > 0) ? -1.0f : 1.0f, yVec };
		D3DXVec2Normalize(&dir, &dir);
		if (coli.obj->bGround)
			static_cast<Unit*>(coli.obj)->Hit(damage, D3DXVECTOR2(dir.x * attackVec.x, dir.y * attackVec.y));
		else
		{
			dir.y = 0;
			static_cast<Unit*>(coli.obj)->Hit(damage, D3DXVECTOR2(dir.x * attackVec.x, dir.y * attackVec.y));
		}

	}
}
