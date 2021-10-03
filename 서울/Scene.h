#pragma once
class Scene
{
public:
	static float score;
	float destScore = 0.0f;

	EnemyManager enemyManager;

	bool stopTime = true;

	bool spawnBoss = false;
	float gameTime = 180.0f;

	int curStage = 0;
	std::random_device rd;
	Scene* nextScene = NULL;

	Player* player = NULL;

	ObjectManager obm;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void UIRender();

	int GetRandNum(int min, int max);
	D3DXVECTOR2 GetRandVec(int minX, int maxX, int minY, int maxY);
	void AddScore(int value);

	void Load();
};

