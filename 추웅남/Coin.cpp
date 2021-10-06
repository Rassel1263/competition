#include "DXUT.h"
#include "Coin.h"

Coin::Coin(D3DXVECTOR2 pos)
{
	this->pos = pos;

	float angle = D3DXToRadian(nowScene->GetRandNum(0, 360));

	destPos = pos + D3DXVECTOR2(cosf(angle), sinf(angle)) * nowScene->GetRandNum(3, 6) * 10;

	spr.LoadAll(L"Assets/Sprites/goods/coins/", 0.05f, true);

	CreateCollider(D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), L"coin");
}

void Coin::Update(float deltaTime)
{
	D3DXVec2Lerp(&pos, &pos, &destPos, 0.1f);

	timer -= deltaTime;

	if (timer <= 0.0f)
	{
		spr.color.a -= deltaTime;
		if (spr.color.a <= 0.0f)
			destroy = true;
	}

	spr.Update(deltaTime);
}

void Coin::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}

void Coin::OnCollision(Collider& coli)
{
	if (coli.tag == L"player")
		nowScene->player->coins++;
}
