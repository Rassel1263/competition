#include "DXUT.h"
#include "LoadSprite.h"

LoadSprite::LoadSprite()
{
	loadBck.LoadAll(L"Assets/Sprites/ui/outgame/loading/gageback.png");
	loadBck.color.a = 0.0f;

	load.LoadAll(L"Assets/Sprites/ui/outgame/loading/gagemain.png");
	load.color.a = 0.0f;
	load.widthRatio = 0.0f;
	TextureManager::GetInstance().SaveFilePath();

	font.LoadAll(L"Assets/Sprites/ui/outgame/intro/introfont.png");

	intro.LoadAll(L"Assets/Sprites/ui/outgame/intro/Scene");
	intro.color.a = 0.0f;

	for (int i = 0; i < 12; ++i)
		threads.emplace_back(&TextureManager::LoadTexture, &TextureManager::GetInstance());

	maxSize = TextureManager::GetInstance().fileSize;

	pos.y = -1100;
}

void LoadSprite::Update(float deltaTime)
{
	size = TextureManager::GetInstance().fileSize;

	if (TextureManager::GetInstance().threadCnt >= 12 && !threadEnd)
	{
		if (loadBck.color.a > 0.0f)
			loadBck.color.a -= deltaTime;
		else
		{
			for (auto& thread : threads)
			{
				if (thread.joinable())
					thread.join();
			}

			threadEnd = true;
		}
	}
	else
	{
		if (loadBck.color.a < 1.0f)
			loadBck.color.a += deltaTime;
		else
		{
			load.widthRatio = 1 - (float)size / (float)maxSize;
		}
	}

	if (Input::GetInstance().KeyDown(VK_SPACE))
		pos.y += 200 * deltaTime;

	pos.y += 100 * deltaTime;

	Intro(deltaTime);

	if (threadEnd && pos.y >= 700)
	{
		nowScene->obm.AddObject(new Main());
		destroy = true;
	}

	load.color.a = loadBck.color.a;
}

void LoadSprite::Render()
{
	intro.Render(RenderInfo{});
	font.Render(RenderInfo{ pos });
	loadBck.Render(RenderInfo{ D3DXVECTOR2(0, -500) });
	load.Render(RenderInfo{ D3DXVECTOR2(0, -500) });
}

void LoadSprite::Intro(float deltaTime)
{
	intro.color.a += deltaTime * destColor * 0.5f;

	if ((intro.color.a <= 0.0f || intro.color.a >= 1.0f) && intro.scene < 4)
	{
		if (intro.color.a <= 0.0f)
			intro.scene++;

		destColor = -destColor;
		intro.color.a = std::clamp(intro.color.a, 0.0f, 1.0f);
	}
}
