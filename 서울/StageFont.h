#pragma once
class StageFont : public ObjectUI
{
public:
	enum class Type
	{
		START,
		CLEAR,
		FAIL
	} type;

	Sprite bck;
	Sprite spr;

	StageFont(Type type);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

