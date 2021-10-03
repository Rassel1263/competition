#pragma once
class LoadSprite  : public Object
{
public:
	std::vector<std::thread> threads;
public:
	LoadSprite();
	~LoadSprite();

	Sprite introFont;
	Sprite intro;

	Sprite loadBck;
	Sprite load;

	int size = 0;
	int maxSize = 0;
	bool threadEnd = false;

	float timer = 0.0f;
	float destColor = 1.0f;
	int index = 0;


	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void NextScene(float deltaTime);
};

