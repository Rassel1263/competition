#include "DXUT.h"
#include "PlayerUI.h"

PlayerUI::PlayerUI(Player * player)
{
	this->player = player;
	SetSprite(L"base2.png", base);

	SetSprite(L"hpBck.png", hpBck);
	SetSprite(L"hp.png", hp);

	SetSprite(L"mpBck.png", mpBck);
	SetSprite(L"mp.png", mp);

	SetSprite(L"healBck.png", healBck);
	SetSprite(L"heal.png", heal);

	SetSprite(L"item1.png", powerUp);
	SetSprite(L"item2.png", grenade);

	SetSprite(L"ComboFont.png", comboLogo);

	SetSprite(L"comboBck.png", comboGB);
	SetSprite(L"combo.png", comboG);

	for (int i = 0; i < 6; ++i)
	{
		if (player->skillEnhance[i])
		{
			Sprite spr;
			spr.LoadAll(L"Assets/Sprites/UI/Player/skill/" + std::to_wstring(i) + L".png");
			spr.bCamera = false;
			skills.push_back(spr);
		}
	}

	hpRI.pos = { -800, -400 };
	mpRI.pos = { -560, -445 };
	healRI.pos = { -600, -290 };
	comboRI.pos = { 800, -100 };
}

void PlayerUI::Update(float deltaTime)
{
	hp.heightRatio = 1 - player->ability.hp / player->ability.maxHp;
	mp.heightRatio = 1 - player->mp / player->maxMp;
	heal.heightRatio = 1 - player->healTime / player->healMaxTime;

	powerUp.heightRatio = 1 - player->powerUpTime / 5.0f;

	UpdateCombo();

	if (nowScene->player->combo > 0)
		comboG.widthRtaio = 1 - nowScene->player->comboInterval / 0.5f;
}

void PlayerUI::Render()
{
	base.Render(RenderInfo{});

	hpBck.Render(hpRI);
	hp.Render(RenderInfo{ D3DXVECTOR2(hpRI.pos.x, hpRI.pos.y + 9) });

	mpBck.Render(mpRI);
	mp.Render(RenderInfo{ D3DXVECTOR2(mpRI.pos.x, mpRI.pos.y + 4) });

	healBck.Render(healRI);
	heal.Render(RenderInfo{ D3DXVECTOR2(healRI.pos.x, healRI.pos.y + 2) });

	if (player->powerUp)
		powerUp.Render(RenderInfo{ D3DXVECTOR2(-180, -450), D3DXVECTOR2(0.7, 0.7) });

	if (player->grenade)
		grenade.Render(RenderInfo{ D3DXVECTOR2(-350, -450), D3DXVECTOR2(0.7, 0.7) });

	comboLogo.Render(RenderInfo{ D3DXVECTOR2(800, 100) });

	int cnt = 0;
	if (nowScene->player->combo > 0)
	{
		comboGB.Render(comboRI);
		comboG.Render(comboRI);

		for (auto& spr : combo)
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(750 + cnt * 50, 0) });
			cnt++;
		}
	}

	cnt = 0;
	for (auto& spr : skills)
	{
		spr.Render(RenderInfo{D3DXVECTOR2(-800, -100 - cnt * 70), D3DXVECTOR2(0.3, 0.3)});
		cnt++;
	}
}

void PlayerUI::UpdateCombo()
{
	if (player->prevCombo != player->combo)
	{
		WCHAR temp[256];
		wsprintf(temp, L"%02d", player->combo);
		std::wstring str = temp;

		combo.resize(str.size());

		int cnt = 0;
		for (auto& spr : combo)
		{
			spr.LoadAll(L"Assets/Sprites/UI/Font/Combo/" + str.substr(cnt, 1) + L".png");
			spr.bCamera = false;

			if(player->combo != 0)
				nowScene->obm.AddObject(new AfterImage(0, spr, RenderInfo{D3DXVECTOR2(750 + cnt* 50, 0)}, NULL, 1100));


			RenderInfo ri;
			cnt++;
		}

		player->prevCombo = player->combo;
	}
}

void PlayerUI::SetSprite(std::wstring name, Sprite & spr)
{
	spr.LoadAll(L"Assets/Sprites/UI/Player/" + name);
	spr.bCamera = false;
}
