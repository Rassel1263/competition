#pragma once
class Main : public Object
{
public:
	int pNum = -1;
	int cNum = 0;

	std::vector<Sprite> ui;

	Main();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void ChoiceBtn();
};

