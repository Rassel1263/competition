#pragma once
class RankingScene : public Scene
{
public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void UIRender() override;
};

