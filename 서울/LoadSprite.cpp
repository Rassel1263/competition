#include "DXUT.h"
#include "LoadSprite.h"

LoadSprite::~LoadSprite()
{
	/*for (auto& thread : threads)
	{
		if (thread.joinable())
			thread.join();
	}*/
}

LoadSprite::LoadSprite()
{
	introFont.LoadAll(L"Assets/Sprites/Intro/font.png");

	loadBck.LoadAll(L"Assets/Sprites/UI/IntroProBck.png");
	loadBck.color.a = 0.0f;
	load.LoadAll(L"Assets/Sprites/UI/IntroPro.png");
	load.color.a = 0.0f;

	load.widthRtaio = 0.0f;

	intro.LoadAll(L"Assets/Sprites/Intro/Intro/");
	intro.color.a = 0.0f;

	pos.y -= 1080;

	TextureManager::GetInstance().SaveFilePath();

	for (int i = 0; i < 12; ++i)
		threads.emplace_back(&TextureManager::LoadTexture, &TextureManager::GetInstance());

	maxSize = TextureManager::GetInstance().fileSize;
}

void LoadSprite::Update(float deltaTime)
{
	size = TextureManager::GetInstance().GetPathsSize();

	if (TextureManager::GetInstance().threadCnt >= 12 && !threadEnd)
	{
		loadBck.color.a -= deltaTime;

		if (loadBck.color.a <= 0.0f)
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
			load.widthRtaio = 1 - size / (float)maxSize;
	}

	if (Input::GetInstance().KeyPress(VK_SPACE))
		pos.y += 200 * deltaTime;

	pos.y += 100 * deltaTime;

	NextScene(deltaTime);

	if (threadEnd && pos.y >= 700)
	{
		nowScene->obm.AddObject(new Main());
		destroy = true;
	}

	load.color.a = loadBck.color.a;
}

void LoadSprite::Render()
{
	intro.Render(RenderInfo{ D3DXVECTOR2(0, 0), D3DXVECTOR2(2, 2) });
	introFont.Render(RenderInfo{ pos });

	if (!threadEnd)
	{
		loadBck.Render(RenderInfo{ D3DXVECTOR2(0, -400) });
		load.Render(RenderInfo{ D3DXVECTOR2(-15, -409) });
	}
}

void LoadSprite::NextScene(float deltaTime)
{
	intro.color.a += deltaTime * destColor * 0.5f;

	if ((intro.color.a >= 1.0f || intro.color.a <= 0.0f ) && intro.scene < 3)
	{
		if (intro.color.a <= 0.0f)
			intro.scene++;

		destColor = -destColor;
		Camera::GetInstance().cameraQuaken = { 20, 20 };
		intro.color.a = std::clamp(intro.color.a, 0.0f, 1.0f);
	}
}
