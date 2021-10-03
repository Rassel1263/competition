#pragma once
class Map : public Object
{
public:
	Sprite spr;

	Map();

	virtual void Update(float deltaTime);
	virtual void Render() override;
};

