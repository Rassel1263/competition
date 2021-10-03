#pragma once
class Fade : public ObjectUI
{
public:
	Sprite spr;
	RenderInfo ri;
	std::function<void()> func;

	bool fill = false;

	Fade(bool fill, std::function<void()> func = NULL);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

