#include "DXUT.h"
#include "Box.h"

Box::Box(D3DXVECTOR2 pos)
{
	this->pos = pos;
	ri.pivot = { 0.5f, 0.0 };
	this->groundPos = pos.y;

	spr.LoadAll(L"Assets/Sprites/box", 0.05f, false);
	
	layer = 1080 - (groundPos + 540);

	CreateCollider(D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 200), L"box");
}

void Box::Update(float deltaTime)
{
	if (hit)
	{
		if (!spr.bAnimation)
		{
			nowScene->obm.AddObject(new Item(nowScene->GetRandNum(1, 2), pos));
			destroy = true;
		}

		spr.Update(deltaTime);
	}
}

void Box::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void Box::OnCollision(Collider & coli)
{
	if (coli.tag == L"playerbullet" || coli.tag == L"playeratk")
	{
		if (abs(groundPos - coli.obj->groundPos) >= 100) return;

		if (!hit)
		{
			SoundManager::GetInstance().Play("Box");
			hit = true;
		}
	}
}
