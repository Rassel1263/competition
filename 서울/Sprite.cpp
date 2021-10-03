#include "DXUT.h"
#include "Sprite.h"

void Sprite::LoadAll(std::wstring filePath, float aniMaxTime, bool aniLoop)
{
	textures.clear();

	if (std::filesystem::is_directory(filePath))
	{
		for (auto& file : std::filesystem::recursive_directory_iterator(filePath))
		{
			if (auto texture = TextureManager::GetInstance().GetTexture(file.path()))
				textures.push_back(texture);
		}
	}
	else
	{
		if (auto texture = TextureManager::GetInstance().GetTexture(filePath))
			textures.push_back(texture);
		else
			textures.push_back(TextureManager::GetInstance().GetTexture(L"EmptyProject.jpg"));
	}

	this->aniMaxTime = aniMaxTime;
	this->bAniLoop = aniLoop;
	this->szScene = textures.size();
}

void Sprite::Update(float deltaTime)
{
	if (!bAnimation || bAniStop) return;

	aniTime += deltaTime;

	if (aniTime >= aniMaxTime)
	{
		aniTime = 0.0f;

		if (scene < szScene - 1)
			++scene;
		else if (bAniLoop)
			scene = 0;
		else
			bAnimation = false;
	}
}

void Sprite::Render(RenderInfo & ri)
{
	CUSTOMVERTEX* v = NULL;
	Game::GetInstance().pVB->Lock(0, 0, (void**)&v, 0);

	v[0].pos = D3DXVECTOR3(0, 0, 0);
	v[0].color = color;
	v[0].uv = D3DXVECTOR2(0.0f, 1.0f);

	v[1].pos = D3DXVECTOR3(GetNowScene()->info.Width * widthRtaio , 0, 0);
	v[1].color = color;
	v[1].uv = D3DXVECTOR2(1.0f * widthRtaio, 1.0f);

	v[2].pos = D3DXVECTOR3(0, GetNowScene()->info.Height * (1 - heightRatio) , 0);
	v[2].color = color;
	v[2].uv = D3DXVECTOR2(0.0f, heightRatio);

	v[3].pos = D3DXVECTOR3(GetNowScene()->info.Width * widthRtaio, GetNowScene()->info.Height * (1 - heightRatio), 0);
	v[3].color = color;
	v[3].uv = D3DXVECTOR2(1 * widthRtaio, heightRatio);

	Game::GetInstance().pVB->Unlock();

	D3DXMATRIX matrix;
	D3DXVECTOR2 centerPos = D3DXVECTOR2(GetNowScene()->info.Width * ri.pivot.x, GetNowScene()->info.Height * ri.pivot.y);
	D3DXMatrixTransformation2D(&matrix, &centerPos, 0, &ri.scale, &centerPos, -D3DXToRadian(ri.rotate), &(ri.pos - centerPos));

	Game::GetInstance().pDevice->SetTransform(D3DTS_WORLD, (bCamera) ? &(matrix * Camera::GetInstance().matWorld) : &matrix);
	Game::GetInstance().pDevice->SetStreamSource(0, Game::GetInstance().pVB, 0, sizeof(CUSTOMVERTEX));
	Game::GetInstance().pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	Game::GetInstance().pDevice->SetTexture(0, GetNowScene()->src);
	Game::GetInstance().pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

const Texture * Sprite::GetNowScene()
{
	return textures[scene];
}

void Sprite::Reset()
{
	bAnimation = true;
	aniTime = 0.0f;
	scene = 0;
}
