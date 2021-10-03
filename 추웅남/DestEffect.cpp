#include "DXUT.h"
#include "DestEffect.h"

DestEffect::DestEffect(D3DXVECTOR2 pos, Sprite spr)
{
	this->pos = pos;
	this->spr = spr;
}

void DestEffect::Update(float deltaTime)
{
	D3DXVec2Lerp(&pos, &pos, &D3DXVECTOR2(Camera::GetInstance().cameraPos.x, Camera::GetInstance().cameraPos.y), 0.1f);
	D3DXVec2Lerp(&ri.scale, &ri.scale, &D3DXVECTOR2(2, 2), 0.1f);

	if (abs(Camera::GetInstance().cameraPos.y - pos.y) <= 100)
	{
		spr.color.a -= deltaTime;

		if (spr.color.a <= 0.0f)
			destroy = true;
	}
}

void DestEffect::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
