#pragma once
class Player;
class PlayerUI : public ObjectUI
{
public:
	Sprite base;
	
	Sprite hpBck;
	Sprite hp;
	RenderInfo hpRI;

	Sprite mpBck;
	Sprite mp;
	RenderInfo mpRI;

	Sprite healBck;
	Sprite heal;
	RenderInfo healRI;

	Sprite powerUp;
	Sprite grenade;

	Sprite comboLogo;
	std::vector<Sprite> combo;

	Sprite comboG;
	Sprite comboGB;
	RenderInfo comboRI;

	std::vector<Sprite> skills;

	Player* player = NULL;

	PlayerUI(Player* player);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void UpdateCombo();
	void SetSprite(std::wstring name, Sprite& spr);
};

