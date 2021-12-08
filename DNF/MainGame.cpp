#include "stdafx.h"
#include "Config.h"
#include "MainGame.h"
#include "BmpImage.h"

HRESULT MainGame::Init()
{
	MGR_TIMER->Init();
	MGR_SCENE->Init();

	GdiplusStartup(&g_gpToken, &g_gpsi, NULL);
	SetTimer(g_hWnd, 0, 10, NULL);

	SceneManager::GetSingleton()->ChangeScene(SCENE_TAG::CharacterSelectScene, SCENE_TAG::TitleScene);

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
	MGR_SCENE->Release();
	MGR_IMAGE->Release();

	GdiplusShutdown(g_gpToken);
	KillTimer(g_hWnd, 0);
}