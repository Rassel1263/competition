#include "DXUT.h"
#include "MiniMap.h"

MiniMap::MiniMap()
{
	sprites[MiniTag::PLAYER].LoadAll(L"Assets/Sprites/ui/ingame/map/player.png");
	sprites[MiniTag::PLAYER].bCamera = false;

	sprites[MiniTag::ENEMY].LoadAll(L"Assets/Sprites/ui/ingame/map/Enemy.png");
	sprites[MiniTag::ENEMY].bCamera = false;

	spr.LoadAll(L"Assets/Sprites/ui/ingame/map.png");
	spr.bCamera = false;
}

void MiniMap::AddMiniObj(MiniInfo info)
{
	miniObj.push_back(info);
}

void MiniMap::SortMiniObj(Unit* unit)
{
	auto lambda = [=](MiniInfo& info) {return info.unit == unit; };

	auto sf = std::find_if(miniObj.begin(), miniObj.end(), lambda);

	if (sf != miniObj.end())
		miniObj.erase(sf);
}

void MiniMap::Update(float deltaTime)
{
}

void MiniMap::Render()
{
	spr.Render(RenderInfo{ D3DXVECTOR2(735, -320) });

	for (auto& obj : miniObj)
	{
		RenderInfo temp;

		if (!nowScene->spawnBoss)
		{
			if (obj.tag == MiniTag::PLAYER)
				temp.pos = D3DXVECTOR2(745, -415);
			else
			{
				temp.pos = (D3DXVECTOR2((obj.unit->pos.x - nowScene->player->pos.x) / 5 + 745,
					(obj.unit->pos.y - nowScene->player->pos.y) / 2.8 - 415));
			}
		}
		else
		{
			temp.pos = (D3DXVECTOR2((obj.unit->pos.x - Camera::GetInstance().cameraPos.x) / 6 + 745,
				(obj.unit->pos.y - Camera::GetInstance().cameraPos.y + 200) / 3.5 - 415));
		}

		if (temp.pos.x > 562 && temp.pos.x < 925 &&
			temp.pos.y > -508 && temp.pos.y < -144)
		{
			sprites[obj.tag].Render(temp);
		}

	}
}

