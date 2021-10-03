#include "DXUT.h"
#include "CalcPage.h"

CalcPage::CalcPage()
{
	bck.LoadAll(L"Assets/Sprites/UI/calcBck.png");
	bck.color.a = 0.0f;
	bck.bCamera = false;

	fontSpr.LoadAll(L"Assets/Sprites/UI/calcFont.png");
	fontSpr.color.a = 0.0f;
	fontSpr.bCamera = false;

	skillSpr.LoadAll(L"Assets/Sprites/UI/calcSkillNum.png");
	skillSpr.color.a = 0.0f;
	skillSpr.bCamera = false;

	fontColor.a = 0.0f;

	// 스킬 강화 정하기
	for (int i = 0; i < 6; ++i)
	{
		if(!nowScene->player->skillEnhance[i])
			skillNums.push_back(i);
	}

	std::default_random_engine rnd(nowScene->rd());
	std::shuffle(skillNums.begin(), skillNums.end(), rnd);

	skills.resize(3);

	for (int i = 0; i < 3; ++i)
	{
		skills[i].LoadAll(L"Assets/Sprites/UI/Player/skill/" + std::to_wstring(skillNums[i]) + L".png");
		skills[i].bCamera = false;
		skills[i].color.a = 0.0f;
	}

	nowScene->score += nowScene->destScore;
	nowScene->destScore = 0.0f;

	nowScene->stopTime = true;

	this->hp = nowScene->player->ability.hp;
	this->maxCombo = nowScene->player->maxCombo;

}

void CalcPage::Update(float deltaTime)
{
	if (index == 0)
	{
		stopTimer -= deltaTime;

		if (stopTimer <= 0.0f)
		{
			bck.color.a += deltaTime;

			if (bck.color.a >= 1.0f)
			{
				if (!drawFont)
				{
					drawFont = true;

					nowScene->obm.AddObject(new Font<float>(L"Score/", hp, D3DXVECTOR2(-100, 300), D3DXVECTOR2(1, 1), 1, 100, layer + 1, &fontColor));
					nowScene->obm.AddObject(new Font<float>(L"Time/", nowScene->gameTime, D3DXVECTOR2(-100, 100), D3DXVECTOR2(1, 1), 1, 100, layer + 1, &fontColor));
					nowScene->obm.AddObject(new Font<float>(L"Combo/", maxCombo, D3DXVECTOR2(-100, -100), D3DXVECTOR2(1, 1), 1, 100, layer + 1, &fontColor));
					nowScene->obm.AddObject(new Font<float>(L"Score/", nowScene->score, D3DXVECTOR2(300, -300), D3DXVECTOR2(1, 1), 1, 100, layer + 1, &fontColor));

					stopTimer = 1.0f;
					index++;
				}
			}
		}
	}
	else if (index == 1)
	{
		if (fontSpr.color.a < 1.0f)
		{
			fontSpr.color.a += deltaTime;
			fontColor.a = fontSpr.color.a;
		}
		else
		{
			stopTimer -= deltaTime;

			if (stopTimer <= 0.0f)
			{
				if (hp > 0)
					Calc(hp, deltaTime);
				else if (nowScene->gameTime > 0.0f)
					Calc(nowScene->gameTime, deltaTime);
				else if (maxCombo > 0)
					Calc(maxCombo, deltaTime);
				else
				{
					if (Input::GetInstance().KeyDown(VK_RETURN))
					{
						if (nowScene->curStage == 3)
							index++;

						index++;

						stopTimer = 1.0f;
					}
				}
			}
		}
	}
	else if (index == 2)
	{
		if (fontSpr.color.a > 0.0f)
		{
			fontSpr.color.a -= deltaTime;
			fontColor.a = fontSpr.color.a;
		}
		else
		{
			if(skillSpr.color.a < 1.0f)
				skillSpr.color.a += deltaTime;
			else
			{
				bool input = false;

				if (Input::GetInstance().KeyDown(0x31))
				{
					EnhanceData::GetInstance().SetEnhance(skillNums[0]);
					nowScene->obm.AddObject(new UIEffect(skills[0], D3DXVECTOR2(-600, 0), 1.0f, layer - 1));
					input = true;
				}
				else if (Input::GetInstance().KeyDown(0x32))
				{
					EnhanceData::GetInstance().SetEnhance(skillNums[1]);
					nowScene->obm.AddObject(new UIEffect(skills[1], D3DXVECTOR2(0, 0), 1.0f, layer - 1));
					input = true;
				}
				else if (Input::GetInstance().KeyDown(0x33))
				{
					EnhanceData::GetInstance().SetEnhance(skillNums[2]);
					nowScene->obm.AddObject(new UIEffect(skills[2], D3DXVECTOR2(600, 0), 1.0f, layer - 1));
					input = true;
				}

				if (input)
					index++;
			}
		}
	}
	else if (index == 3)
	{
		stopTimer -= deltaTime;

		if (stopTimer <= 0.0f)
		{
			auto lambda = [] {Game::GetInstance().ChangeScene(nowScene->nextScene); };
			nowScene->obm.AddObject(new Fade(true, lambda));

			index++;
		}
	}
}

void CalcPage::Render()
{
	bck.Render(RenderInfo{});

	fontSpr.Render(RenderInfo{});

	skillSpr.Render(RenderInfo{});
	int cnt = 0;
	for (auto& spr : skills)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-600 + cnt * 600, 0.0f) });
		spr.color.a = skillSpr.color.a;
		cnt++;
	}
}

void CalcPage::Calc(float & num, float deltaTime)
{
	float temp = num;
	num -= deltaTime * 100;

	if (num <= 0.0f)
		num = 0.0f;

	nowScene->score += temp - num;
}
