#pragma once
class Option : public Object
{
public:
	int cNum = 0;
	int pNum = 0;

	Sprite bck;
	Sprite bckFont;
	Sprite border;
	std::vector<Sprite> font;
	Sprite arrow;

public:
	Option();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void MoveBtn();
};

