#pragma once

class Time : public Singleton<Time>
{
public:
	long currentTime = 0;
	long lastTime = 0;
	long deltaTime = 0;
	float fDeltaTime = 0;
	float timeScale = 1.0f;
	float unscaleTime = 0.0f;

public:
	void Init()
	{
		currentTime = timeGetTime();
		lastTime = currentTime;
	}

	void Update()
	{
		if (Input::GetInstance().KeyDown(VK_CONTROL))
			timeScale = 0.1f;
		if (Input::GetInstance().keyUp(VK_CONTROL))
			timeScale = 1.0f;

		if (Input::GetInstance().KeyDown(VK_SHIFT))
			timeScale = 10.0f;
		if (Input::GetInstance().keyUp(VK_SHIFT))
			timeScale = 1.0f;

		currentTime = timeGetTime();
		deltaTime = currentTime - lastTime;
		fDeltaTime = (float)deltaTime / 1000.0f;
		unscaleTime = fDeltaTime;
		lastTime = currentTime;
	}
};

