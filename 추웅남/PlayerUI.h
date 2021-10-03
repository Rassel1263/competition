#pragma once
class PlayerUI : public ObjectUI
{
public:
	Player* player = NULL;

	Sprite base;

	// 체력
	Sprite hpBck;
	Sprite hp;
	Sprite speedUp;
	Sprite invincible;
	RenderInfo hpRI;

	// 이동속도
	Sprite spdKey;
	Sprite km;
	RenderInfo keyInfo;

	// 아이콘
	Sprite weapons;
	Sprite skill1;
	Sprite skill2;
	std::vector<Sprite> coolTime;
	std::vector<RenderInfo> coolRI;

	// 폰트
	std::vector<std::vector<Sprite>> fonts;
	std::vector<RenderInfo> fontRI;


public:
	PlayerUI(Player* player);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void FontUpdate(std::vector<Sprite>& font, float num, std::wstring name);
	void FontRender(std::vector<Sprite>& font, RenderInfo ri, float kerning);

	void SetSprite(std::wstring path, Sprite& spr);
};

