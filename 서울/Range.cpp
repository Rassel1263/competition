#include "DXUT.h"
#include "Range.h"

Range::Range(Unit * owner, std::wstring targetName, D3DXVECTOR2 offset, D3DXVECTOR2 min, D3DXVECTOR2 max, D3DXCOLOR color, float detectGroundPos)
{
	this->owner = owner;
	this->target = targetName;
	this->offset = offset;
	this->detectGroundPos = detectGroundPos;
	
	CreateCollider(min, max, L"range", color);
}

void Range::Update(float deltaTime)
{
	pos = owner->pos + offset;
}

void Range::Render()
{
	Object::Render();
}

void Range::OnCollision(Collider & coli)
{
	if (coli.tag == target)
	{
		if(abs(pos.y - coli.obj->groundPos) <= detectGroundPos)
			detect = true;
	}
}
