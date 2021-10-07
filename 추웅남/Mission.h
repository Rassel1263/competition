#pragma once
class Mission : public ObjectUI
{
public:
	float stopTime = 0.5f;

	Sprite spr;

	RenderInfo ri;

	int index = 0;

	struct FontInfo
	{
		RenderInfo ri;
		D3DXVECTOR2 destPos = { 0, 0 };
	};

	std::vector<Sprite> font;
	std::vector<FontInfo> fontRI;

	Mission();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void CheckMission();
};

