#include "DXUT.h"
#include "Collider.h"

Collider::Collider(std::wstring tag, Object* obj, AABB* aabb, D3DXCOLOR color)
{
    this->aabb = *aabb;

    this->tag = tag;
    this->obj = obj;
    this->color = color;
    this->obj->bCollider = true;
}

bool IntersectCollider(Collider& coli1, Collider& coli2)
{
    return IntersectAABB(coli1.obj->pos + coli1.aabb.min, coli1.obj->pos + coli1.aabb.max,
        coli2.obj->pos + coli2.aabb.min, coli2.obj->pos + coli2.aabb.max);
}

bool IntersectAABB(D3DXVECTOR2 min1, D3DXVECTOR2 max1, D3DXVECTOR2 min2, D3DXVECTOR2 max2)
{
    return (min1.x < max2.x) && (min2.x < max1.x) && (min1.y < max2.y) && (min2.y < max1.y);
}
