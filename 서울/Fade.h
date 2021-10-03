#pragma once
class Fade : public ObjectUI
{
public:
	bool fill = false;

	Sprite spr;
	RenderInfo ri;

	std::function<void()> func= NULL; 

	Fade(bool fill, std::function<void()> func = NULL);

	virtual void Update(float deltaTime);
	virtual void Render();
};

