#include "DXUT.h"
#include "AfterImage.h"

AfterImage::AfterImage(Sprite spr, RenderInfo ri, D3DXCOLOR color, float time, int layer)
{
	this->index = 1;

	this->pos = ri.pos;
	this->spr = spr;
	this->ri = ri;
	this->spr.color = color;

	this->maxTime = time;
	this->timer = time;

	this->layer = layer;

	colorShader = new ColorShader();
}

AfterImage::AfterImage(int scene, Sprite spr, RenderInfo ri, D3DXVECTOR2 * fallowPos, int layer)
{
	this->index = 2;
	this->pos = ri.pos;

	this->spr = spr;
	this->spr.scene = scene;

	this->ri = ri;
	this->ri.scale = { ri.scale.x * 2, 2 };

	this->spr.color = D3DCOLOR_ARGB(125, 255, 255, 255);

	this->fallowPos = fallowPos;

	this->layer = layer;
	colorShader = new ColorShader();
}

void AfterImage::Update(float deltaTime)
{
	if (index == 1)
	{
		timer -= deltaTime;

		spr.color.a = timer / maxTime;

		if (spr.color.a <= 0.0f)
			destroy = true;
	}
	else
	{
		if (fallowPos)
			pos = *fallowPos;

		D3DXVec2Lerp(&ri.scale, &ri.scale, &D3DXVECTOR2(0, 0), 0.05f);

		if (abs(ri.scale.x) <= 1.0f || abs(ri.scale.y) <= 1.0f)
			destroy = true;
	}
}

void AfterImage::Render()
{
	ri.pos = pos;
	colorShader->Render(colorShader, spr, ri, D3DXVECTOR4(spr.color.r, spr.color.g, spr.color.g, spr.color.a));
}
