#include "DXUT.h"
#include "Main.h"

Main::Main()
{
	ui.resize(8);

	for (int i = 0; i < 4; ++i)
		ui[i].LoadAll(L"Assets/Sprites/ui/outgame/Menu/Button/" + std::to_wstring(i) + L".png");

	ui[4].LoadAll(L"Assets/Sprites/ui/outgame/Menu/menuselect.png");
	ui[5].LoadAll(L"Assets/Sprites/ui/outgame/Menu/mainlogo.png");
	ui[6].LoadAll(L"Assets/Sprites/ui/outgame/Menu/deco.png");
	ui[7].LoadAll(L"Assets/Sprites/ui/outgame/Menu/background", 0.05f, true);

	nowScene->obm.AddObject(new Fade(false));
}

void Main::Update(float deltaTime)
{
	UpdateBtn();

	if (Input::GetInstance().KeyDown(VK_RETURN) && !static_cast<MainScene*>(nowScene)->input)
	{
		static_cast<MainScene*>(nowScene)->input = true;
		SoundManager::GetInstance().Play("ClickBtn");

		switch(cNum)
		{
		case 0:
			nowScene->obm.AddObject(new Fade(true, [] {Game::GetInstance().ChangeScene(new GameScene()); }));
			break;
		case 1:
			nowScene->obm.AddObject(new Rank());
			break;
		case 2:
			nowScene->obm.AddObject(new Help());
			break;
		case 3:
			nowScene->obm.AddObject(new Fade(true, [] {PostQuitMessage(0); }));
			break;

		}
	}

	ui[7].Update(deltaTime);
}

void Main::Render()
{
	ui[7].Render(RenderInfo{});
	ui[6].Render(RenderInfo{});
	ui[5].Render(RenderInfo{});
	ui[4].Render(RenderInfo{ D3DXVECTOR2(50, -100 - cNum * 100) });

	for (int i = 0; i < 4; ++i)
	{
		ui[i].Render(RenderInfo{ D3DXVECTOR2(30, -100 - i * 100) });
	}

}

void Main::UpdateBtn()
{
	pNum = cNum;

	if (Input::GetInstance().KeyDown(VK_DOWN))
		cNum++;
	if (Input::GetInstance().KeyDown(VK_UP))
		cNum--;

	cNum = std::clamp(cNum, 0, 3);

	if (pNum != cNum)
	{
		SoundManager::GetInstance().Play("MoveBtn");
	}
}

