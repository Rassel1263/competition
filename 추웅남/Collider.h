#pragma once

class Object;
class Collider 
{
public:
	struct AABB
	{
		D3DXVECTOR2 min = { 0, 0 }, max = { 0, 0 };
	} aabb;

	Collider(std::wstring tag, Object* obj, AABB* aabb, D3DXCOLOR color);

	std::wstring tag = L"";
	Object* obj = NULL;
	D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
};

bool IntersectCollider(Collider& coli1, Collider& coli2);
bool IntersectAABB(D3DXVECTOR2 min1, D3DXVECTOR2 max1, D3DXVECTOR2 min2, D3DXVECTOR2 max2);

