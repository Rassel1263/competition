#include "DXUT.h"
#include "Nuclear.h"

Nuclear::Nuclear(D3DXVECTOR2 pos)
{
	this->pos = pos;
	this->groundPos = pos.y;

	spr.LoadAll(L"Assets/Sprites/effect/Player/nuclear", 0.03f, false);
}

void Nuclear::Update(float deltaTime)
{
	if (nowScene->player->nuclear)
	{
		if (Input::GetInstance().KeyPress(VK_LEFT))
			pos.x -= 500 * deltaTime;
		if(Input::GetInstance().KeyPress(VK_RIGHT))
			pos.x += 500 * deltaTime;
		if(Input::GetInstance().KeyPress(VK_DOWN))
			pos.y -= 500 * deltaTime;
		if(Input::GetInstance().KeyPress(VK_UP))
			pos.y += 500 * deltaTime;
	}
	else
	{
		if (!spr.bAnimation)
			destroy = true;

		if (spr.scene == 33 && !onAttack)
		{
			groundPos = pos.y;

			onAttack = true;
			nowScene->obm.AddObject(new SkillEffect(2, 0.5f));

			nowScene->obm.AddObject(new AttackCollider(L"player", pos + D3DXVECTOR2(0, 100), D3DXVECTOR2(0, 0), D3DXVECTOR2(-500, -200), D3DXVECTOR2(500, 200), 60, D3DXVECTOR2(0, 0), 0.0f, groundPos + 100, 0.1f));
			nowScene->obm.AddObject(new AttackCollider(L"player", pos, D3DXVECTOR2(0, 0), D3DXVECTOR2(-500, -200), D3DXVECTOR2(500, 200), 60, D3DXVECTOR2(0, 0), 0.0f, groundPos, 0.1f));
			nowScene->obm.AddObject(new AttackCollider(L"player", pos + D3DXVECTOR2(0, -100), D3DXVECTOR2(0, 0), D3DXVECTOR2(-500, -200), D3DXVECTOR2(500, 200), 60, D3DXVECTOR2(0, 0), 0.0f, groundPos - 100, 0.1f));

			Camera::GetInstance().cameraQuaken = { 20, 20 };
			SoundManager::GetInstance().Play("NuclearBoom");
		}

		spr.Update(deltaTime);
	}
}

void Nuclear::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
