#include "DXUT.h"
#include "StageHelp.h"

StageHelp::StageHelp(int stage)
{
	this->stage = stage;

	if (stage < 3)
		SoundManager::GetInstance().Play("start");

	prevSpr.LoadAll(L"Assets/Sprites/ui/ingame/StageHelp/" + std::to_wstring(stage - 1) + L".png");
	prevSpr.color.a = 0.0f;
	prevSpr.bCamera = false;

	spr.LoadAll(L"Assets/Sprites/ui/ingame/StageHelp/" + std::to_wstring(stage) + L".png");
	spr.color.a = 0.0f;
	spr.bCamera = false;

	complete.LoadAll(L"Assets/Sprites/ui/ingame/StageHelp/4.png");
	complete.color.a = 0.0f;
	complete.bCamera = false;

	layer = 3;
}

void StageHelp::Update(float deltaTime)
{
	if (index == 0)
	{
		if (stopTime > 0.0f)
			stopTime -= deltaTime;
		else
		{
			if(prevSpr.color.a < 1.0f)
				prevSpr.color.a += deltaTime;
			else
			{
				stopTime = 1.0f;
				index++;
			}
		}
	}
	else if (index == 1)
	{
		if (stopTime > 0.0f)
			stopTime -= deltaTime;
		else
		{
			if (spr.color.a < 1.0f)
				spr.color.a += deltaTime;
			else
			{
				if (stage == 3)
				{
					stopTime = 0.5f;
					index++;
				}

				index++;
			}
		}
	}
	else if (index == 2)
	{
		prevSpr.color.a -= deltaTime;
		spr.color.a -= deltaTime;

		if (spr.color.a <= 0.0f)
		{
			destroy = true;
			nowScene->player->intro = false;
			nowScene->stopTime = false;
		}
	}
	else if (index == 3)
	{
		if (complete.color.a < 1.0f)
			complete.color.a += deltaTime;
		else
		{
			stopTime -= deltaTime;

			if (stopTime <= 0.0f)
			{
				index++;
				nowScene->obm.AddObject(new Fade(true, [] {Game::GetInstance().ChangeScene(new RankingScene()); }));
			}
		}
	}
}

void StageHelp::Render()
{
	prevSpr.Render(RenderInfo{});
	spr.Render(RenderInfo{});
	complete.Render(RenderInfo{});
}
