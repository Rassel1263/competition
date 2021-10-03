#pragma once
class Main : public Object
{
public:
	std::vector<Sprite> ui;

	int pNum = 0;
	int cNum = 0;

	Main();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void UpdateBtn();
};

