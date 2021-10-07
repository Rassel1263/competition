//-----------------------------------------------------------------------------
// File: Textures.cpp
//
// Desc: Better than just lights and materials, 3D objects look much more
//       convincing when texture-mapped. Textures can be thought of as a sort
//       of wallpaper, that is shrinkwrapped to fit a texture. Textures are
//       typically loaded from image files, and D3DX provides a utility to
//       function to do this for us. Like a vertex buffer, Textures have
//       Lock() and Unlock() functions to access (read or write) the image
//       data. Textures have a width, height, miplevel, and pixel format. The
//       miplevel is for "mipmapped" Textures, an advanced performance-
//       enhancing feature which uses lower resolutions of the texture for
//       objects in the distance where detail is less noticeable. The pixel
//       format determines how the colors are stored in a texel. The most
//       common formats are the 16-bit R5G6B5 format (5 bits of red, 6-bits of
//       green and 5 bits of blue) and the 32-bit A8R8G8B8 format (8 bits each
//       of alpha, red, green, and blue).
//
//       Textures are associated with geometry through texture coordinates.
//       Each vertex has one or more sets of texture coordinates, which are
//       named tu and tv and range from 0.0 to 1.0. Texture coordinates can be
//       supplied by the geometry, or can be automatically generated using
//       Direct3D texture coordinate generation (which is an advanced feature).
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include "DXUT.h"

#define ALTENTER 1234



//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (Game::GetInstance().pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = 1920;
	d3dpp.BackBufferHeight = 1080;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create the D3DDevice
	if (FAILED(Game::GetInstance().pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		&d3dpp, &Game::GetInstance().pDevice)))
	{
		return E_FAIL;
	}

	Game::GetInstance().Init();

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	// Clear the backbuffer and the zbuffer
	Game::GetInstance().pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(Game::GetInstance().pDevice->BeginScene()))
	{

		Game::GetInstance().Render();
		// End the scene
		Game::GetInstance().pDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	Game::GetInstance().pDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SETCURSOR:
		SetCursor(NULL);
		break;
	case WM_HOTKEY:
		switch (wParam)
		{
		case ALTENTER:
			static bool showToggle = true;
			showToggle = !showToggle;

			SetWindowLongPtr(hWnd, GWL_STYLE, (showToggle) ? WS_POPUP : WS_OVERLAPPEDWINDOW);
			MoveWindow(hWnd, 300, 200, 1280, 720, false);
			ShowWindow(hWnd, (showToggle) ? SW_SHOWMAXIMIZED : SW_SHOWDEFAULT);
			return 0;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT main(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D Tutorial", NULL
	};
	RegisterClassEx(&wc);


	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);

	// Create the application's window
	HWND hWnd = CreateWindow(L"D3D Tutorial", L"D3D Tutorial 05: Textures",
		WS_VISIBLE | WS_POPUP, 0, 0, w, h,
		NULL, NULL, wc.hInstance, NULL);

	RegisterHotKey(hWnd, ALTENTER, MOD_ALT, VK_RETURN);

	// Initialize Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		// Create the scene geometry
			// Show the window
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		// Enter the message loop
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				Game::GetInstance().Update();
				Render();
			}
		}
	}

	UnregisterClass(L"D3D Tutorial", wc.hInstance);
	return 0;
}



