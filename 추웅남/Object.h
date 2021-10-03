#pragma once

class Object
{
public:
	bool destroy = false;
	bool bCollider = false;
	int layer = 0;

	std::vector<Collider> bodies;

	D3DXVECTOR2 pos = { 0, 0 };

	void CreateCollider(D3DXVECTOR2 min, D3DXVECTOR2 max, std::wstring tag, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0));

	virtual ~Object();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnCollision(Collider& coli);
};

class ObjectUI
{
public:
	bool destroy = false;
	int layer = 0;
	D3DXVECTOR2 pos = { 0, 0 };

	virtual ~ObjectUI();
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
	void Collision();
	void Update(float deltaTime);
	void Render();
	void UIRender();
};
