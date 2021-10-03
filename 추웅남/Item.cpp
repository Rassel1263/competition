#include "DXUT.h"
#include "Item.h"

Item::Item(D3DXVECTOR2 pos, int index)
{
	this->index = index;
	this->pos = pos;

	spr.LoadAll(L"Assets/Sprites/Item/" + std::to_wstring(index), 0.05f, true);

	CreateCollider(D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), L"item");
}

void Item::Update(float deltaTime)
{
	timer -= deltaTime;

	if (timer <= 0.0f)
		destroy = true;

	spr.Update(deltaTime);
}

void Item::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}

void Item::OnCollision(Collider& coli)
{
	if (coli.tag == L"player")
	{
		nowScene->obm.AddObject(new DestEffect(pos, spr));
		nowScene->obm.AddObject(new Effect(L"ItemObtain", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
		SoundManager::GetInstance().Play("Item");
		nowScene->player->GetEffective(index);
		destroy = true;
	}
}
