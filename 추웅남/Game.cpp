#include "DXUT.h"
#include "Game.h"

Scene* nowScene = NULL;

Game::~Game()
{
	SAFE_RELEASE(pD3D);
	SAFE_RELEASE(pDevice);
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pLine);
}

HRESULT Game::Init()
{
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CUSTOMVERTEX) * 4, 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &pVB, 0)))
	{
		return E_FAIL;
	}

	D3DXCreateLine(pDevice, &pLine);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	ChangeScene(new MainScene());

	Input::GetInstance().Init();
	Time::GetInstance().Init();
	Camera::GetInstance().Init();
}

void Game::Update()
{
	Input::GetInstance().Update();
	Time::GetInstance().Update();

	if (nextScene)
	{
		Camera::GetInstance().cameraPos = { 0, 0 };
		Camera::GetInstance().destCameraPos = { 0, 0 };

		Camera::GetInstance().cameraScale = { 1, 1 };
		Camera::GetInstance().destCameraScale = { 1, 1 };

		SAFE_DELETE(nowScene);
		nowScene = nextScene;
		nowScene->Init();
		nextScene = NULL;
	}

	if (Input::GetInstance().KeyDown(VK_CONTROL))
		Time::GetInstance().timeScale = 10.0f;
	if (Input::GetInstance().KeyUp(VK_CONTROL))
		Time::GetInstance().timeScale = 1.0f;

	if (Input::GetInstance().KeyDown(VK_F2))
		pause = !pause;

	if (!pause)
	{
		if (nowScene)
			nowScene->Update(Time::GetInstance().fDeltaTime * Time::GetInstance().timeScale);
	}

	Camera::GetInstance().Update();
}

void Game::Render()
{
	if (nowScene)
	{
		nowScene->Render();

		D3DXMATRIX matrix;
		D3DXMatrixOrthoLH(&matrix, Game::GetInstance().screenWidth, Game::GetInstance().screenHeight, 0.01f, 1000.0f);
		pDevice->SetTransform(D3DTS_WORLD, &matrix);

		nowScene->UIRender();
	}
}

void Game::DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXMATRIX mat, D3DXCOLOR color)
{
	pLine->SetWidth(2.0f);
	pLine->Begin();
	D3DXVECTOR3 v[] = { D3DXVECTOR3(p1.x, p1.y, 0.0f), D3DXVECTOR3(p2.x, p2.y, 0.0f) };
	D3DXMATRIX retMat = mat * Camera::GetInstance().matView * Camera::GetInstance().matWorld * Camera::GetInstance().matProj;
	pLine->DrawTransform(v, 2, &retMat, color);
	pLine->End();
}

void Game::ChangeScene(Scene* nextScene)
{
	this->nextScene = nextScene;

}
