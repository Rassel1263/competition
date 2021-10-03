#include "DXUT.h"
#include "Main.h"

Main::Main()
{
	ui.resize(8);

	for (int i = 0; i < 5; ++i)
	{
		ui[i].LoadAll(L"Assets/Sprites/UI/main/menu/" + std::to_wstring(i));
		ui[i].scene = 1;
	}

	ui[0].scene = 0;

	ui[5].LoadAll(L"Assets/Sprites/UI/main/menu/select.png");
	ui[6].LoadAll(L"Assets/Sprites/UI/main/mainlogo", 0.05f, true);
	ui[7].LoadAll(L"Assets/Sprites/UI/main/background", 0.05f, true);

	nowScene->obm.AddObject(new Fade(false));
}

void Main::Update(float deltaTime)
{
	ChoiceBtn();

	if (Input::GetInstance().KeyDown(VK_RETURN) && !static_cast<MainScene*>(nowScene)->input)
	{
		static_cast<MainScene*>(nowScene)->input = true;

		SoundManager::GetInstance().Play("ClickBtn");

		switch (cNum)
		{
		case 0:
		{		
			auto lambda = [] {Game::GetInstance().ChangeScene(new GameScene()); };
			nowScene->obm.AddObject(new Fade(true, lambda));
			break;
		}
		case 1:
			nowScene->obm.AddObject(new Rank());
			break;
		case 2:
			nowScene->obm.AddObject(new Help());
			break;
		case 3:
			nowScene->obm.AddObject(new Option());
			break;
		case 4:
		{
			auto lambda = [] { PostQuitMessage(0); };
			nowScene->obm.AddObject(new Fade(true, lambda));
			break;
		}
		}
	}

	ui[6].Update(deltaTime);
	ui[7].Update(deltaTime);
}

void Main::Render()
{
	ui[7].Render(RenderInfo{D3DXVECTOR2(0, 0), D3DXVECTOR2(2, 2)});
	ui[6].Render(RenderInfo{D3DXVECTOR2(-450, 200)});
	ui[5].Render(RenderInfo{D3DXVECTOR2(-875 + cNum * 350, -400)});

	for (int i = 0; i < 5; ++i)
		ui[i].Render(RenderInfo{ D3DXVECTOR2(-700 + i * 350, -400) });
}

void Main::ChoiceBtn()
{
	if (static_cast<MainScene*>(nowScene)->input) return;

	pNum = cNum;

	if (Input::GetInstance().KeyDown(VK_LEFT))
		cNum--;

	if (Input::GetInstance().KeyDown(VK_RIGHT))
		cNum++;

	cNum = std::clamp(cNum, 0, 4);

	if (cNum != pNum)
	{
		SoundManager::GetInstance().Play("MoveBtn");

		ui[cNum].scene = 0;
		ui[pNum].scene = 1;
	}

}
