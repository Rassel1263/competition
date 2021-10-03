#pragma once
class LoadSprite : public Object
{
public:
	std::vector<std::thread> threads;

	Sprite font;
	Sprite intro;

	Sprite loadBck;
	Sprite load;

	int size = 0;
	int maxSize = 0;

	float destColor = 1.0f;

	bool threadEnd = false;

	LoadSprite();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void Intro(float deltaTime);
};

