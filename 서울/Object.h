#pragma once
class Object
{
public:
	bool bCollider = false;
	bool destroy = false;
	D3DXVECTOR2 pos = { 0, 0 };
	std::vector<Collider> bodies;
	int layer = 0;

	// ¹°¸®
	bool bRigid = false;
	bool bGround = false;

	D3DXVECTOR2 fixedPos = { 0, 0 };
	D3DXVECTOR2 force = { 0, 0 };
	D3DXVECTOR2 velocity = { 0, 0 };
	float mass = 1.0f;
	float gravity = 0.0f;
	float groundPos = 0.0f;

public:
	virtual ~Object();
	Object();
	void SetRigid();
	void CreateCollider(D3DXVECTOR2 min, D3DXVECTOR2 max, std::wstring tag, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0));
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnCollision(Collider& coli);
};

class ObjectUI
{
public:
	bool destroy = false;
	D3DXVECTOR2 pos = { 0, 0 };
	int layer = 0;

public:
	virtual ~ObjectUI();
	ObjectUI();
	virtual void Update(float deltaTime);
	virtual void Render();
};

class ObjectManager
{
private:
	std::vector<Object*> addObjects;
	std::vector<Object*> objects;
	std::vector<ObjectUI*> addUIObjects;
	std::vector<ObjectUI*> uiObjects;

public:
	~ObjectManager();
	void AddObject(Object* obj);
	void AddObject(ObjectUI* obj);

	void Update(float deltaTime);
	void Collision();
	void Render();
	void UIRender();
};


