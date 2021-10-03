#pragma once
class Boss1 : public CBoss
{
public:
	Boss1();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void SetImages();

	virtual int ChoosePattern();
	virtual bool Pattern1(float deltaTime);
	virtual bool Pattern2(float deltaTime);
	virtual bool Pattern3(float deltaTime);
};

