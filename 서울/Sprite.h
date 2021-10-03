#pragma once

struct RenderInfo
{
	D3DXVECTOR2 pos = { 0,0 };
	D3DXVECTOR2 scale = { 1, 1 };
	D3DXVECTOR2 pivot = { 0.5, 0.5 };
	float rotate = 0.0f;
};

class Sprite
{
public:
	bool bAnimation = true;
	bool bAniLoop = true;
	bool bCamera = true;
	bool bAniStop = false;

	float aniTime = 0.0f;
	float aniMaxTime = 0.05f;

	float widthRtaio = 1.0f;
	float heightRatio = 0.0f;

	int scene = 0;
	int szScene = 0;

	std::vector<const Texture*> textures;

	D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);

public:
	void LoadAll(std::wstring filePath, float aniMaxTime = 0.05f, bool aniLoop = false);

	void Update(float deltaTime);
	void Render(RenderInfo& ri);
	const Texture* GetNowScene();
	void Reset();
};

