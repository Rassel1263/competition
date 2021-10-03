#include "DXUT.h"
#include "Cloud.h"

Cloud::Cloud()
{
	pos = nowScene->player->pos + D3DXVECTOR2(nowScene->GetRandNum(-1000, 1000), 800);

	spr.LoadAll(L"Assets/Sprites/map/Cloud/" + std::to_wstring(nowScene->GetRandNum(0, 3)) + L".png");

	speed = nowScene->GetRandNum(1, 3) * 100;

	layer = 20;
}

void Cloud::Update(float deltaTime)
{
	pos.y -= deltaTime * speed;

	if (pos.y < Camera::GetInstance().cameraPos.y - 1000)
		destroy = true;

}

void Cloud::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
