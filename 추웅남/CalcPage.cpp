#include "DXUT.h"
#include "CalcPage.h"

CalcPage::CalcPage()
{
	bck.LoadAll(L"Assets/Sprites/message/stageResult/stageresult.png");
	bck.color.a = 0.0f;
	bck.bCamera = false;

	nowScene->score += nowScene->destScore;
	nowScene->destScore = 0.0f;

	this->hp = nowScene->player->ability.hp;
	this->kill = nowScene->player->kill;

	color.a = 0.0f;

	layer = 3;
}

void CalcPage::Update(float deltaTime)
{
	if (index == 0)
	{
		if (stopTime > 0.0f)
			stopTime -= deltaTime;
		else
		{
			if (bck.color.a < 1.0f)
				bck.color.a += deltaTime;
			else
			{
				nowScene->obm.AddObject(new Font<float>(L"Score/", hp, D3DXVECTOR2(-100, 280), D3DXVECTOR2(2, 2), 100, 1, layer + 1, &color));
				nowScene->obm.AddObject(new Font<float>(L"Score/", nowScene->gameTime, D3DXVECTOR2(-100, 80), D3DXVECTOR2(2, 2), 100, 1, layer + 1, &color));
				nowScene->obm.AddObject(new Font<float>(L"Score/", kill, D3DXVECTOR2(-100, -120), D3DXVECTOR2(2, 2), 100, 1, layer + 1, &color));
				nowScene->obm.AddObject(new Font<float>(L"Score/", nowScene->score, D3DXVECTOR2(200, -360), D3DXVECTOR2(2, 2), 100, 2, layer + 1, &color));

				index++;
			}
		}
	}
	else if (index == 1)
	{
		if (color.a <= 1.0f)
			color.a += deltaTime;
		else
		{
			if (hp > 0)
				Calc(hp, deltaTime);
			else if(nowScene->gameTime > 0.0f)
				Calc(nowScene->gameTime, deltaTime);
			else if(kill > 0.0f)
				Calc(kill, deltaTime);
			else
			{
				if (Input::GetInstance().KeyDown(VK_RETURN))
				{
					if (nowScene->curStage == 1)
						nowScene->obm.AddObject(new Fade(true, [] {Game::GetInstance().ChangeScene(nowScene->nextScene); }));
					else
						index++;
				}
			}
		}
	}
	else if (index == 2)
	{
		if (bck.color.a > 0.0f)
			bck.color.a -= deltaTime;
		else
		{
			nowScene->obm.AddObject(new StageHelp(3));
			destroy = true;
		}

		color = bck.color.a;
	}
}

void CalcPage::Render()
{
	bck.Render(RenderInfo{});
}

void CalcPage::Calc(float& num, float deltaTime)
{
	float temp = num;

	num -= deltaTime * 100;

	if (num <= 0)
		num = 0;

	nowScene->score += temp - num;
}
