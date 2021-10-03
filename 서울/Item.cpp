#include "DXUT.h"
#include "Item.h"

Item::Item(int index, D3DXVECTOR2 pos)
{
	this->pos = pos;
	ri.pivot = { 0.5f, 0.0 };
	this->groundPos = pos.y;
	this->index = index;

	spr.LoadAll(L"Assets/Sprites/Item/" + std::to_wstring(index), 0.1f, true);
	CreateCollider(D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 150), L"item");

	layer = 1080 - (groundPos + 540);
}

void Item::Update(float deltaTime)
{
	spr.Update(deltaTime);
}

void Item::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}

void Item::OnCollision(Collider & coli)
{
	if (coli.tag == L"player")
	{
		destroy = true;
		nowScene->player->GetItem(index);
		SoundManager::GetInstance().Play("Item");
	}
}
