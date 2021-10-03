#pragma once
class MainScene : public Scene
{
public:
	bool input = false;

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void UIRender() override;
};

