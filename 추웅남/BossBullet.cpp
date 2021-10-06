#include "DXUT.h"
#include "BossBullet.h"

BossBullet::BossBullet(int index, D3DXVECTOR2 pos, float angle, float damage, float speed, float timer)
{
	this->index = index;

	if (index == 0)
		spr.LoadAll(L"Assets/Sprites/bullet/bossBullet/bullet.png");
	else
		spr.LoadAll(L"Assets/Sprites/bullet/bossBullet/Normal/" +std::to_wstring(index) + L".png");

	this->angle = angle;
	this->damage = damage;
	this->speed = speed;

	this->timer = timer;
	this->func = func;

	layer = 4;

	CreateCollider(D3DXVECTOR2(-40, -40), D3DXVECTOR2(40, 40), L"enemy");
}

void BossBullet::Update(float deltaTime)
{
	if (index == 0)
	{
		timer -= deltaTime;

		if (timer <= 0.0f)
		{
			for (int i = 0; i < 6; ++i)
				nowScene->obm.AddObject(new BossBullet(nowScene->GetRandNum(1, 7), pos, D3DXToRadian(i * 60), 5, 700));

			destroy = true;
		}
	}

	pos += D3DXVECTOR2(cosf(angle), sinf(angle))* deltaTime * speed;
}

void BossBullet::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void BossBullet::OnCollision(Collider& coli)
{
	if (coli.tag == L"player")
		destroy = true;
}
