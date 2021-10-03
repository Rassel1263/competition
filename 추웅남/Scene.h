#pragma once
class Scene
{
public:
	int curStage = 0;
	Scene* nextScene = NULL;

	static float score;
	float destScore = 0.0f;
	float finishPos = 25000;

	bool spawnBoss = false;

	bool stopTime = true;
	float gameTime = 180.0f;
	float minute = 0.0f;
	float second = 0.0f;
	float millisecond = 0.0f;

	float cloudTimer = 0.0f;

	Player* player = NULL;
	MsgBox* msgBox = NULL;
	MiniMap* miniMap = NULL;

	EnemyManager enemyManager;
	ObstacleManager obstacleManager;
	ObjectManager obm;

	std::random_device rd;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void UIRender();

	int GetRandNum(int min, int max);
	D3DXVECTOR2 GetRandVec(int minX, int maxX, int minY, int maxY);
	float GetAngleFromTarget(D3DXVECTOR2 pos, D3DXVECTOR2 targetPos);

};

