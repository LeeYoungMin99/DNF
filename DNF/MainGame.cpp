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

	backBuffer = new BmpImage;
	backBuffer->Init("Image/BackGround.bmp", WIN_SIZE_X, WIN_SIZE_Y);

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
	HDC hBackBufferDC = backBuffer->GetMemDC();

	MGR_SCENE->Render(hBackBufferDC);
	MGR_TIMER->Render(hBackBufferDC);

	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	MGR_TIMER->Release();

	MGR_KEY->Release();

	MGR_SCENE->Release();

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
