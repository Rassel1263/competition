#include "DXUT.h"
#include "BossUI.h"

BossUI::BossUI(CBoss* boss)
{
	this->boss = boss;

	hpBck.LoadAll(L"Assets/Sprites/UI/enemy/bossHpBck.png");
	hpBck.bCamera = false;
	hpBck.color.a = 0.0f;

	hp.LoadAll(L"Assets/Sprites/UI/enemy/bossHp.png");
	hp.bCamera = false;
	hp.color.a = 0.0f;
	hp.widthRtaio = 0.0f;

	spBck.LoadAll(L"Assets/Sprites/UI/enemy/superArmorBck.png");
	spBck.bCamera = false;
	spBck.color.a = 0.0f;

	sp.LoadAll(L"Assets/Sprites/UI/enemy/superArmor.png");
	sp.bCamera = false;
	sp.color.a = 0.0f;
	sp.widthRtaio = 0.0f;

	hpRI.pos = { 0, 400 };
	spRI.pos = { 0, 350 };
}

void BossUI::Update(float deltaTime)
{
	if (index == 0)
	{
		if (hpBck.color.a < 1.0f)
		{
			hpBck.color.a += deltaTime;
			spBck.color.a = hpBck.color.a;
		}
		else
		{
			if (hp.widthRtaio < 1.0f)
			{
				hp.widthRtaio += deltaTime;
				sp.widthRtaio = hp.widthRtaio;
			}
			else
				index++;
		}

		hp.color.a = hpBck.color.a;
		sp.color.a = spBck.color.a;
	}
	else if (index == 1)
	{
		hp.widthRtaio = boss->ability.hp / boss->ability.maxHp;
		sp.widthRtaio = boss->sp / boss->maxSp;
	}
}

void BossUI::Render()
{
	spBck.Render(spRI);
	sp.Render(spRI);

	hpBck.Render(hpRI);
	hp.Render(RenderInfo{ D3DXVECTOR2(hpRI.pos.x - 14, hpRI.pos.y - 9) });

}
