#include "DXUT.h"
#include "Option.h"

Option::Option()
{
	bck.LoadAll(L"Assets/Sprites/UI/main/Option/bck.png");
	bckFont.LoadAll(L"Assets/Sprites/UI/main/Option/font.png");
	border.LoadAll(L"Assets/Sprites/UI/main/Option/border.png");
	font.resize(2);
	font[0].LoadAll(L"Assets/Sprites/UI/main/Option/active");
	font[1].LoadAll(L"Assets/Sprites/UI/main/Option/active");
	arrow.LoadAll(L"Assets/Sprites/UI/main/Option/arrow.png");
}

void Option::Update(float deltaTime)
{
	if (static_cast<MainScene*>(nowScene)->input)
	{
		if (bck.color.a < 1.0f)
			bck.color.a += deltaTime;

		MoveBtn();

		if(font[1].scene == 0)
		{
			SetWindowLongPtr(Game::GetInstance().hWnd, GWL_STYLE, WS_POPUP);
			ShowWindow(Game::GetInstance().hWnd, SW_SHOWMAXIMIZED);
		}
		else
		{
			SetWindowLongPtr(Game::GetInstance().hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			MoveWindow(Game::GetInstance().hWnd, 300, 200, 1280, 720, false);
			ShowWindow(Game::GetInstance().hWnd, SW_SHOWDEFAULT);
		}

		if (Input::GetInstance().KeyDown(VK_RETURN))
		{
			static_cast<MainScene*>(nowScene)->input = false;
		}
	}
	else
	{
		bck.color.a -= deltaTime;
		border.color.a = bck.color.a;
		bckFont.color.a = bck.color.a;
		for (auto& spr : font)
			spr.color.a = bck.color.a;
		arrow.color.a = bck.color.a;

		if (bck.color.a <= 0.0f)
			destroy = true;
	}

	bck.color.a = bck.color.a;
	bck.color.a = std::clamp(bck.color.a, 0.0f, 0.7f);
}

void Option::Render()
{
	bck.Render(RenderInfo{});
	border.Render(RenderInfo{D3DXVECTOR2(0, 220 + cNum * -180)});
	bckFont.Render(RenderInfo{});

	int cnt = 0;
	for (auto& spr : font)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(600, 220 + cnt * -180) });
		cnt++;
	}

	if (cNum == 0 || cNum == 1)
		arrow.Render(RenderInfo{ D3DXVECTOR2(600, 220 + cNum * -180) });
}

void Option::MoveBtn()
{
	if (Input::GetInstance().KeyDown(VK_DOWN))
		cNum++;

	if (Input::GetInstance().KeyDown(VK_UP))
		cNum--;

	cNum = std::clamp(cNum, 0, 3);

	if (cNum == 0 || cNum == 1)
	{
		if(Input::GetInstance().KeyDown(VK_LEFT))
			font[cNum].scene--;
		if (Input::GetInstance().KeyDown(VK_RIGHT))
			font[cNum].scene++;
		font[cNum].scene = std::clamp(font[cNum].scene, 0, 1);
	}
}
