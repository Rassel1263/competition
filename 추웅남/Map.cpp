#include "DXUT.h"
#include "Map.h"

Map::Map()
{
	spr.LoadAll(L"Assets/Sprites/map/Ocean/layer0_0.png");
	spr.widthRatio = 5;
	spr.heightRatio = -50;
}

void Map::Update(float deltaTime)
{
}

void Map::Render()
{
	spr.Render(RenderInfo{ D3DXVECTOR2(-3840, 0) });
}
