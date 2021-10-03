#include "DXUT.h"
#include "StageFont.h"

StageFont::StageFont(Type type)
{
	bck.LoadAll(L"Assets/Sprites/effect/bck.png");
	bck.bCamera = false;
	spr.bCamera = false;

	this->type = type;

	if (type == Type::START)
	{
		spr.LoadAll(L"Assets/Sprites/effect/StageStart/" + std::to_wstring(nowScene->curStage), 0.03f, false);
	}
	else if (type == Type::CLEAR)
	{
		SoundManager::GetInstance().StopAll();
		SoundManager::GetInstance().Play("Result");
		spr.LoadAll(L"Assets/Sprites/effect/StageClear/", 0.05f, false);
	}
	else if (type == Type::FAIL)
	{
		spr.LoadAll(L"Assets/Sprites/effect/StageFail/", 0.05f, false);
		bck.color.a = 0.0f;
	}
}

void StageFont::Update(float deltaTime)
{
	if (type == Type::START)
	{
		if (!spr.bAnimation)
		{
			nowScene->stopTime = false;
			nowScene->player->stop = false;

			bck.color.a -= deltaTime * 2;

			if (bck.color.a <= 0.0f)
			{
				SoundManager::GetInstance().Play("Fight");
				destroy = true;
			}
		}
	}
	else if (type == Type::CLEAR)
	{
		if (!spr.bAnimation)
		{
			spr.color.a -= deltaTime * 0.5f;

			if (spr.color.a <= 0.0f)
			{
				nowScene->obm.AddObject(new CalcPage());
				destroy = true;
			}
		}
	}
	else if (type == Type::FAIL)
	{
		if (!spr.bAnimation)
		{
			bck.color.a += deltaTime * 0.5f;
			spr.color.a -= deltaTime * 0.5f;

			if (bck.color.a >= 1.0f)
			{
				Game::GetInstance().ChangeScene(new MainScene());
			}
		}
	}

	spr.Update(deltaTime);
}

void StageFont::Render()
{ 
	if (type != Type::CLEAR)
		bck.Render(RenderInfo{});

	spr.Render(RenderInfo{});
}
