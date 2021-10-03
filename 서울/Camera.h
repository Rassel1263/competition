#pragma once
class Camera : public Singleton<Camera>
{
public:
	D3DXMATRIX matView;
	D3DXMATRIX matWorld;
	D3DXMATRIX matProj;

	D3DXVECTOR2 cameraPos = { 0, 0 };
	D3DXVECTOR2 cameraScale = { 1, 1 };
	D3DXVECTOR2 cameraQuaken = { 0, 0 };
	D3DXVECTOR2 destCameraPos = { 0, 0 };
	D3DXVECTOR2 destCameraScale = { 1, 1 };
	D3DXVECTOR2 destCameraQuaken = { 0, 0 };

public:
	void Init();
	void Update();
};

