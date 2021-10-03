#pragma once

class Time : public Singleton<Time>
{
public:
	long currentTime = 0;
	long lastTime = 0;
	long deltaTime = 0;
	float fDeltaTime = 0.0f;
	float timeScale = 1.0f;
	float unscaleTime = 0.0f;

	void Init()
	{
		currentTime = timeGetTime();
		lastTime = currentTime;
	}

	void Update()
	{
		currentTime = timeGetTime();
		deltaTime = currentTime - lastTime;
		fDeltaTime = (float)deltaTime / 1000.0f;
		unscaleTime = fDeltaTime;
		lastTime = currentTime;
	}
};
