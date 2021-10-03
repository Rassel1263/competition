#pragma once
class Map : public Object
{
public:
	Sprite layer1;
	Sprite layer2;
	Sprite layer3;

	int widthRatio = 0;

	Map(float widthRatio);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

