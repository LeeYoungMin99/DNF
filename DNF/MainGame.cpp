#include "stdafx.h"
#include "Config.h"
#include "MainGame.h"
#include "BmpImage.h"

HRESULT MainGame::Init()
{
	MGR_KEY->Init();
	MGR_TIMER->Init();
	MGR_SCENE->Init();

	GdiplusStartup(&g_gpToken, &g_gpsi, NULL);
	SetTimer(g_hWnd, 0, 10, NULL);

	SceneManager::GetSingleton()->ChangeScene("CharacterSelectScene", "TitleScene");

	mpBackBuffer = new BmpImage;
	mpBackBuffer->Init("Image/BackGround.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	return S_OK;
}

void MainGame::Update()
{
	MGR_TIMER->Update();

	MGR_SCENE->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = mpBackBuffer->GetMemDC();

	MGR_SCENE->Render(hBackBufferDC);
	MGR_TIMER->Render(hBackBufferDC);

	mpBackBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(mpBackBuffer);

	MGR_TIMER->Release();

	MGR_KEY->Release();

	MGR_SCENE->Release();

	GdiplusShutdown(g_gpToken);
	KillTimer(g_hWnd, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
