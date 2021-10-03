#include "DXUT.h"
#include "Damage.h"

Damage::Damage(D3DXVECTOR2 pos, int damage)
{
	this->pos = pos;
	this->pos.x += nowScene->GetRandNum(-10, 10);
	std::wstring str = std::to_wstring(damage);

	spr.resize(str.size());

	int cnt = 0;
	for (auto& s : spr)
	{
		s.LoadAll(L"Assets/Sprites/UI/Font/Combo/" + str.substr(cnt, 1) + L".png");
		cnt++;
	}
}

void Damage::Update(float deltaTime)
{
	alpha -= deltaTime;

	if (alpha <= 0.0f)
		destroy = true;

	pos.y += deltaTime * 60;
}

void Damage::Render()
{
	int cnt = 0;
	for (auto& s : spr)
	{
		ri.pos = D3DXVECTOR2(pos.x + cnt * 50, pos.y);
		s.Render(RenderInfo{ri.pos, D3DXVECTOR2(0.8, 0.8)});
		s.color.a = alpha;
		cnt++;
	}
}
