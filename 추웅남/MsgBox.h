#pragma once
class MsgBox : public ObjectUI
{
public:
	struct MsgInfo
	{
		Sprite human;
		Sprite msg;
		RenderInfo ri;
		bool bMsg = false;
		float stopTime = 1.0f;
		int index = 0;

		void Reset()
		{
			bMsg = false;
			stopTime = 1.0f;
			index = 0;
		}
	};

	std::vector<MsgInfo> messages;

	MsgBox();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void SpawnMsg(std::wstring message, int index);
};

