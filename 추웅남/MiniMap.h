#pragma once

enum class MiniTag
{
	PLAYER,
	ENEMY,
};

class MiniMap : public ObjectUI
{
public:
	struct MiniInfo
	{
		MiniTag tag;
		Unit* unit = NULL;
	};

	Sprite spr;

	std::map<MiniTag, Sprite> sprites;
	std::vector<MiniInfo> miniObj;

	MiniMap();

	void AddMiniObj(MiniInfo info);
	void SortMiniObj(Unit* unit);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

