#include "DXUT.h"
#include "Airsupport.h"

Airsupport::Airsupport()
{
	SoundManager::GetInstance().Play("airStart");
	SoundManager::GetInstance().Play("airMove");

	spr.LoadAll(L"Assets/Sprites/effect/AirSupport", 0.05f, false);
	spr.bCamera = false;

	layer = 15;
}

void Airsupport::Update(float deltaTime)
{
	if (!spr.bAnimation)
		destroy = true;

	if (spr.scene == 9 || spr.scene == 17 || spr.scene == 22)
	{
		if (!onAttack)
		{
			Camera::GetInstance().cameraQuaken = { 15, 15 };
			for (auto& enemy : nowScene->enemyManager.allEnemys)
			{
				if (enemy->pos.x < Camera::GetInstance().cameraPos.x + 1100 && enemy->pos.x > Camera::GetInstance().cameraPos.x - 1100 &&
					enemy->pos.y < Camera::GetInstance().cameraPos.y + 650 && enemy->pos.y > Camera::GetInstance().cameraPos.y - 650)
				{
					SoundManager::GetInstance().Play("airBoom");
					enemy->Hit(30);
				}
			}

			onAttack = true;
		}
		else
			onAttack = false;
	}

	spr.Update(deltaTime);
}

void Airsupport::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
