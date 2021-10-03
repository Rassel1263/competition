#pragma once

// A structure for our custom vertex type. We added texture coordinates
struct CUSTOMVERTEX
{
	D3DXVECTOR3 pos; // The position
	D3DCOLOR color;    // The color
	D3DXVECTOR2 uv;   // The texture coordinates
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)


class Game :public Singleton<Game>
{
public:
	LPDIRECT3D9             pD3D = NULL; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9       pDevice = NULL; // Our rendering device
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL; // Buffer to hold vertices
	LPD3DXLINE pLine = NULL;

	int screenWidth = 1920;
	int screenHeight = 1080;

	bool pause = false;

	Scene* nextScene = NULL;

public:
	~Game();
	HRESULT Init();
	void Update();
	void Render();
	void DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXMATRIX mat, D3DXCOLOR color);
	void ChangeScene(Scene* nextScene);
};

