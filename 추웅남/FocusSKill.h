#pragma once
class FocusSKill : public ObjectUI
{
public:
	Sprite bck;
	Sprite gauge;

	FocusSKill();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

