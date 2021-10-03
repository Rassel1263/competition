#pragma once
class Help : public Object
{
public:
	Sprite bck;
	Sprite spr;

	Help();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

