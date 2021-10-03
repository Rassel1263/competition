#include "DXUT.h"
#include "Spectrum.h"

Spectrum::Spectrum(int index, Sprite spr, RenderInfo ri, int layer, float attackTime, float attackTimer)
{
	this->index = index;
	this->spr = spr;
	this->ri = ri;
	this->attackTime = attackTime;
	this->attackTimer = attackTimer;

	this->groundPos = ri.pos.y;

	colorShader = new ColorShader();
}

void Spectrum::Update(float deltaTime)
{
	if (!spr.bAnimation)
		destroy = true;

	attackTimer += deltaTime;

	if (index == 3)
	{
		if ((spr.scene > 2 && spr.scene < 14) || 
			(spr.scene > 19 && spr.scene < 33))
		{
			if (attackTimer >= attackTime)
			{
				static bool change = false;
				D3DXVECTOR2 offset = { 230, 250 };

				(change) ? offset.y += 10 : offset.y -= 10;

				nowScene->obm.AddObject(new Bullet(L"player", pos + offset, D3DXVECTOR2(ri.scale.x,0), 5, 1000, Bullet::Type::BASIC, groundPos));

				attackTimer = 0.0f;
				change = !change;
			}
		}
	}
	else if (index == 4)
	{
		if (spr.scene > 8)
		{
			if (attackTimer >= attackTime)
			{
				nowScene->obm.AddObject(new Bullet(L"player", pos + D3DXVECTOR2(250, 200), D3DXVECTOR2(ri.scale.x, 0), 10, 1500, Bullet::Type::MACHINEGUN, groundPos));

				attackTimer = 0.0f;
			}
		}
	}

	spr.Update(deltaTime);
}

void Spectrum::Render()
{
	colorShader->Render(colorShader, spr, ri, D3DXVECTOR4(0, 0, 0, 0.5f));
}
