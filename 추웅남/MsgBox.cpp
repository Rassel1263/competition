#include "DXUT.h"
#include "MsgBox.h"

MsgBox::MsgBox()
{
	messages.resize(2);

	messages[0].human.LoadAll(L"Assets/Sprites/ui/ingame/messagebox.png");
	messages[0].human.color.a = 0.0f;
	messages[0].msg.color.a = 0.0f;
	messages[0].human.bCamera = false;
	messages[0].msg.bCamera = false;
	messages[0].ri.pos = D3DXVECTOR2(800, -20);


	messages[1].human.LoadAll(L"Assets/Sprites/ui/ingame/messagebox2.png");
	messages[1].human.color.a = 0.0f;
	messages[1].msg.color.a = 0.0f;
	messages[1].human.bCamera = false;
	messages[1].msg.bCamera = false;
	messages[1].ri.pos = D3DXVECTOR2(800, 100);
}

void MsgBox::Update(float deltaTime)
{
	for (auto& msg : messages)
	{
		if(msg.bMsg)
		{
			if (msg.index == 0)
			{
				if (msg.human.color.a < 1.0f)
					msg.human.color.a += deltaTime;
				else
					msg.index++;
			}
			else if (msg.index == 1)
			{
				if (msg.stopTime > 0.0f)
					msg.stopTime -= deltaTime;
				else
				{
					if (msg.human.color.a > 0.0f)
						msg.human.color.a -= deltaTime;
					else
						msg.Reset();
				}
			}

			msg.msg.color = msg.human.color;
		}
	}
}

void MsgBox::Render()
{
	for (auto& msg : messages)
	{
		if (msg.bMsg)
		{
			msg.human.Render(msg.ri);
			msg.msg.Render(RenderInfo{ D3DXVECTOR2(msg.ri.pos.x - 130, msg.ri.pos.y + 80) });
		}
	}
}

void MsgBox::SpawnMsg(std::wstring message, int index)
{
	if (!messages[index].bMsg)
	{
		if (index == 0)
			SoundManager::GetInstance().Play("msg" + std::to_string(nowScene->GetRandNum(1, 3)));
		else
			SoundManager::GetInstance().Play("skillMsg");

		messages[index].bMsg = true;
	}
	messages[index].msg.LoadAll(L"Assets/Sprites/ui/ingame/Message/" + message + L".png");
}
