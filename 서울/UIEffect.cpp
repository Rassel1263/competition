#include "DXUT.h"
#include "UIEffect.h"

UIEffect::UIEffect(Sprite spr, D3DXVECTOR2 pos, float visibleTime, int layer)
{
	this->spr = spr;

	this->pos = pos;
	
	this->timer = visibleTime;
	this->maxTime = visibleTime;

	this->layer = layer;
}

void UIEffect::Update(float deltaTime)
{
	timer -= deltaTime;

	spr.color.a = timer / maxTime;

	ri.scale += D3DXVECTOR2(deltaTime, deltaTime) * 1.5f;

	if (timer <= 0.0f)
		destroy = true;

}

void UIEffect::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
