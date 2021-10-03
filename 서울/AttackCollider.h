#pragma once
class AttackCollider : public Object
{
public:
	std::wstring tag = L"";
	D3DXVECTOR2 offset = { 0, 0 };
	D3DXVECTOR2 ownerPos = { 0, 0 };
	D3DXVECTOR2* fallowPos = NULL;
	float damage = 0.0f;
	D3DXVECTOR2 attackVec = { 0, 0 };
	float yVec = 0.0f;
	float time = 0.0f;

	AttackCollider(std::wstring tag, D3DXVECTOR2 pos, D3DXVECTOR2 offset, D3DXVECTOR2 min, D3DXVECTOR2 max, float damage, D3DXVECTOR2 attackVec, float yVec, float groundPos, float time);
	AttackCollider(std::wstring tag, D3DXVECTOR2* pos, D3DXVECTOR2 offset, D3DXVECTOR2 min, D3DXVECTOR2 max, float damage, D3DXVECTOR2 attackVec, float yVec, float groundPos, float time);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

