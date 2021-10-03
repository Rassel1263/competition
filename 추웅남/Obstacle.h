#pragma once
class Obstacle : public Object
{
public:
	enum class Type
	{
		GARABAGE,
		MINE,
		ROCK,
	} type;

	Sprite spr;
	RenderInfo ri;

	Sprite range;

	Obstacle(D3DXVECTOR2 pos, Type type);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

class ObstacleManager
{
public:
	float gInterval = 0.0f;
	float gDistance = 0.0f;
	float rInterval = 0.0f;
	float rDistance = 0.0f;

public:
	void Init(float gIntraval, float rInterval);

	void Spawner(float playerDistance);
};

