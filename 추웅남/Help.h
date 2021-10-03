#pragma once
class Help : public Object
{
public:
	Sprite spr;

	Help();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

