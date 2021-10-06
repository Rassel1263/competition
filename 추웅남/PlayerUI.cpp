#include "DXUT.h"
#include "PlayerUI.h"

PlayerUI::PlayerUI(Player* player)
{
	this->player = player;

	SetSprite(L"base.png", base);

	SetSprite(L"speed.png", spdKey);
	SetSprite(L"km.png", km);
	keyInfo.pos = { -498, -422 };

	SetSprite(L"hp_outline.png", hpBck);
	SetSprite(L"hp_ingage.png", hp);
	SetSprite(L"speedUp.png", speedUp);
	SetSprite(L"invincible.png", invincible);
	hpRI.pos = {-470, -200};

	SetSprite(L"weapon/allWeapon.png", weapons);

	SetSprite(L"skill1.png", skill1);
	SetSprite(L"skill2.png", skill2);

	SetSprite(L"coin.png", coinIcon);

	coolTime.resize(6);
	coolRI.resize(6);
	for (int i = 0; i < 6; ++i)
	{
		if (i < 4)
			SetSprite(L"weapon/coolTime.png", coolTime[i]);
		else
			SetSprite(L"skills/skillCool.png", coolTime[i]);
	}

	coolRI[0].pos = { -860, -247 };
	coolRI[1].pos = { -681, -247 };
	coolRI[2].pos = { -860, -417 };
	coolRI[3].pos = { -681, -417 };
	coolRI[4].pos = { -735, -130 };
	coolRI[5].pos = { -665, -130 };

	fonts.resize(7);
	fontRI.resize(7);

	fontRI[0].pos = D3DXVECTOR2(keyInfo.pos.x + 38, keyInfo.pos.y);
	fontRI[0].scale = D3DXVECTOR2(0.4, 0.4);
	fontRI[1].pos = D3DXVECTOR2(-775, -50);
	fontRI[2].pos = D3DXVECTOR2(-875, -288);
	fontRI[3].pos = D3DXVECTOR2(-695, -288);
	fontRI[4].pos = D3DXVECTOR2(-875, -458);
	fontRI[5].pos = D3DXVECTOR2(-695, -458);
	fontRI[6].pos = D3DXVECTOR2(-480, -490);

	for (int i = 2; i < 6; ++i)
		fontRI[i].scale = { 0.5, 0.5 };

	layer = 2;
}

void PlayerUI::Update(float deltaTime)
{
	D3DXVec2Lerp(&keyInfo.pos, &keyInfo.pos, &D3DXVECTOR2(keyInfo.pos.x, -464 + player->speedLevel * 42), 0.1f);
	fontRI[0].pos.y = keyInfo.pos.y;

	hp.heightRatio = 1 - player->ability.hp / player->ability.maxHp;
	speedUp.heightRatio = hp.heightRatio;
	invincible.heightRatio = hp.heightRatio;

	speedUp.widthRatio = player->speedUpTime / 5.0f;
	invincible.widthRatio = player->invincibleTime / 2.0f;


	coolTime[0].heightRatio = 1 - static_cast<MachineGun*>(player->weapons[0])->reloadTimer / static_cast<MachineGun*>(player->weapons[0])->reloadTime;
	coolTime[1].heightRatio = 1 - static_cast<NavanGun*>(player->weapons[1])->reloadTimer / static_cast<NavanGun*>(player->weapons[1])->reloadTime;
	coolTime[2].heightRatio = player->weapons[2]->shootTimer / player->weapons[2]->shootInterval;
	coolTime[3].heightRatio = player->weapons[3]->shootTimer / player->weapons[3]->shootInterval;
	coolTime[4].heightRatio = 1 - player->skill1CoolTimer / player->skill1CoolTime;
	coolTime[5].heightRatio = 1 - player->skill2CoolTimer / player->skill2CoolTime;


	FontUpdate(fonts[0], player->ability.speed / 5, L"Number/");
	FontUpdate(fonts[1], nowScene->finishPos, L"Score/");
	for (int i = 2; i < 6; ++i)
		FontUpdate(fonts[i], player->weapons[i - 2]->bulletAmount, L"Number/");

	FontUpdate(fonts[6], player->coins, L"Score/");
}

void PlayerUI::Render()
{
	base.Render(RenderInfo{});
	spdKey.Render(keyInfo);
	km.Render(RenderInfo{ D3DXVECTOR2(-700, -50) });
	weapons.Render(RenderInfo{ D3DXVECTOR2(-770, -330) });

	hp.Render(hpRI);
	hpBck.Render(hpRI);
	speedUp.Render(hpRI);
	invincible.Render(hpRI);

	coinIcon.Render((RenderInfo{ D3DXVECTOR2(-550, -490), D3DXVECTOR2(2.5, 2.5) }));

	skill1.Render(coolRI[4]);
	skill2.Render(coolRI[5]);

	FontRender(fonts[0], fontRI[0], 10);
	FontRender(fonts[1], fontRI[1], 35);

	for (int i = 2; i < 6; ++i)
		FontRender(fonts[i], fontRI[i], 15);

	FontRender(fonts[6], fontRI[6], 35, 2);

	for (int i = 0; i < 6; ++i)
		coolTime[i].Render(coolRI[i]);
}

void PlayerUI::FontUpdate(std::vector<Sprite>& font, float num, std::wstring name)
{
	std::wstring str = std::to_wstring((int)num);
	font.resize(str.size());

	int cnt = 0;
	for (auto& spr : font)
	{
		spr.bCamera = false;
		spr.LoadAll(L"Assets/Sprites/ui/Font/" + name + str.substr(cnt, 1) + L".png");
		cnt++;
	}
}

void PlayerUI::FontRender(std::vector<Sprite>& font, RenderInfo ri, float kerning, int index)
{
	if (index == 1)
	{
		int size = font.size();

		for (int i = size - 1; i >= 0; --i)
		{
			RenderInfo temp;
			temp.scale = ri.scale;
			temp.pos = ri.pos + D3DXVECTOR2(-kerning * i, 0);
			font[size - 1 - i].Render(temp);
		}
	}
	else
	{
		int cnt = 0;
		for (auto& spr : font)
		{
			RenderInfo temp;
			temp.scale = ri.scale;
			temp.pos = ri.pos + D3DXVECTOR2(kerning * cnt, 0);
			spr.Render(temp);
			cnt++;
		}
	}
}

void PlayerUI::SetSprite(std::wstring path, Sprite& spr)
{
	spr.LoadAll(L"Assets/Sprites/ui/ingame/" + path);
	spr.bCamera = false;
}
