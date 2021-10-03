#include "DXUT.h"
#include "StageFont.h"

StageFont::StageFont(Type type)
{
	this->type = type;

	bck.LoadAll(L"Assets/Sprites/black.png");

	if (type == Type::START)
		spr.LoadAll(L"Assets/Sprites/message/stageStart/" + std::to_wstring(nowScene->curStage), 0.03f, false);
	else if (type == Type::CLEAR)
		spr.LoadAll(L"Assets/Sprites/message/stageClear", 0.05f, false);
	else
	{
		spr.LoadAll(L"Assets/Sprites/message/Gameover", 0.05f, false);
		bck.color.a = 0.0f;
	}

	spr.bCamera = false;
	bck.bCamera = false;

	layer = 3;
}

void StageFont::Update(float deltaTime)
{
	if (type == Type::START)
	{
		if (!spr.bAnimation)
		{
			bck.color.a -= deltaTime;
			if (bck.color.a <= 0.0f)
			{
				nowScene->obm.AddObject(new StageHelp(nowScene->curStage));
				destroy = true;
			}
		}
	}
	else if (type == Type::CLEAR)
	{
		if (!spr.bAnimation)
		{
			nowScene->obm.AddObject(new CalcPage());
			destroy = true;
		}
	}
	else
	{
		if (!spr.bAnimation)
		{
			spr.color.a -= deltaTime;
			bck.color.a += deltaTime;

			if (bck.color.a >= 1.0f)
			{
				Time::GetInstance().timeScale = 1.0f;
				Game::GetInstance().ChangeScene(new MainScene());
			}
		}
	}

	spr.Update(Time::GetInstance().unscaleTime);
}

void StageFont::Render()
{
	if (type != Type::CLEAR)
		bck.Render(RenderInfo{});

	spr.Render(RenderInfo{});
}
