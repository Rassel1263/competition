#pragma once

class Unit;
class Range : public Object
{
public:
	Unit* owner = NULL;
	bool detect = false;
	std::wstring target = L"";
	D3DXVECTOR2 offset = { 0, 0 };

	float detectGroundPos = 0.0f;

	Range(Unit* owner, std::wstring targetName, D3DXVECTOR2 offset, D3DXVECTOR2 min, D3DXVECTOR2 max, D3DXCOLOR color, float detectGroundPos  = 100);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

