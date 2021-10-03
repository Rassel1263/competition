#include "DXUT.h"
#include "Object.h"

Object::~Object()
{
}

Object::Object()
{
}

void Object::SetRigid()
{
	gravity = 9.8f;
	bRigid = true;
}

void Object::CreateCollider(D3DXVECTOR2 min, D3DXVECTOR2 max, std::wstring tag, D3DXCOLOR color)
{
	Collider::AABB aabb = { min ,max };

	bodies.push_back(Collider(tag, this, &aabb, color));
}

void Object::Update(float deltaTime)
{
	if (bRigid)
	{
		if (!bGround)
			force.y -= gravity * 20 * mass * deltaTime;

		velocity.x += force.x * (1 / mass) * 10;
		velocity.y += force.y * (1 / mass) * 10;

		force = { 0, 0 };
		fixedPos = pos;
		pos += velocity * deltaTime;

		if (abs(velocity.x) >= 100)
			velocity.x -= (bGround ? 100 : 10) * velocity.x / abs(velocity.x) * min(abs(velocity.x), 100) * deltaTime;
		else
			velocity.x = 0;

		if (pos.y <= groundPos)
		{

			bGround = true;
			pos.y = groundPos;
		}
		else
			bGround = false;
	}
}

void Object::Render()
{
#ifdef _DEBUG  
	if (bCollider)
	{
		for (auto& body : bodies)
		{
			D3DXMATRIX matrix;
			D3DXMatrixTranslation(&matrix, pos.x, pos.y, 0.0f);

			Game::GetInstance().DrawLine(body.aabb.min, D3DXVECTOR2(body.aabb.max.x, body.aabb.min.y), matrix, body.color);
			Game::GetInstance().DrawLine(D3DXVECTOR2(body.aabb.max.x, body.aabb.min.y), body.aabb.max, matrix, body.color);
			Game::GetInstance().DrawLine(body.aabb.max, D3DXVECTOR2(body.aabb.min.x, body.aabb.max.y), matrix, body.color);
			Game::GetInstance().DrawLine(D3DXVECTOR2(body.aabb.min.x, body.aabb.max.y), body.aabb.min, matrix, body.color);
		}
	}
#endif //  
}

void Object::OnCollision(Collider & coli)
{
}

ObjectUI::~ObjectUI()
{
}

ObjectUI::ObjectUI()
{
}

void ObjectUI::Update(float deltaTime)
{
}

void ObjectUI::Render()
{
}

ObjectManager::~ObjectManager()
{
	for (auto& obj : addObjects)
		SAFE_DELETE(obj);

	for (auto& obj : objects)
		SAFE_DELETE(obj);

	for (auto& obj : addUIObjects)
		SAFE_DELETE(obj);

	for (auto& obj : uiObjects)
		SAFE_DELETE(obj);
}

void ObjectManager::AddObject(Object * obj)
{
	addObjects.push_back(obj);
}

void ObjectManager::AddObject(ObjectUI * obj)
{
	addUIObjects.push_back(obj);
}

void ObjectManager::Update(float deltaTime)
{
	objects.insert(objects.end(), addObjects.begin(), addObjects.end());
	addObjects.clear();

	uiObjects.insert(uiObjects.end(), addUIObjects.begin(), addUIObjects.end());
	addUIObjects.clear();

	std::sort(objects.begin(), objects.end(), [](Object* lhs, Object* rhs) {return lhs->layer < rhs->layer; });
	std::sort(uiObjects.begin(), uiObjects.end(), [](ObjectUI* lhs, ObjectUI* rhs) {return lhs->layer < rhs->layer; });

	for (auto& obj : objects)
		obj->Update(deltaTime);

	for (auto& obj : uiObjects)
		obj->Update(deltaTime);

	for (auto it = objects.begin(); it != objects.end();)
	{
		if ((*it)->destroy)
		{
			delete *it;
			it = objects.erase(it);
		}
		else
			++it;
	}

	for (auto it = uiObjects.begin(); it != uiObjects.end();)
	{
		if ((*it)->destroy)
		{
			delete *it;
			it = uiObjects.erase(it);
		}
		else
			++it;
	}
}

void ObjectManager::Collision()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		for (auto it2 = it + 1; it2 != objects.end(); ++it2)
		{
			if (!(*it)->bCollider || !(*it2)->bCollider) continue;

			for (auto& body : (*it)->bodies)
			{
				for (auto& body2 : (*it2)->bodies)
				{
					if (IntersectCollider(body, body2))
					{
						(*it)->OnCollision(body2);
						(*it2)->OnCollision(body);
					}
				}
			}
		}
	}
}

void ObjectManager::Render()
{
	for (auto& obj : objects)
		obj->Render();
}

void ObjectManager::UIRender()
{
	for (auto& obj : uiObjects)
		obj->Render();
}
