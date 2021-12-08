#include "stdafx.h"
#include "Config.h"
#include "MainGame.h"
#include "BmpImage.h"

HRESULT MainGame::Init()
{
	Input::Init(g_hWnd);
	Timer::Init();

	MGR_SCENE->Init();

	GdiplusStartup(&g_gpToken, &g_gpsi, NULL);

	MGR_SCENE->ChangeScene(SCENE_TAG::CharacterSelectScene, SCENE_TAG::TitleScene);

	mpBackBuffer = MGR_IMAGE->AddImage("Image/BackGround.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	return S_OK;
}

void MainGame::Update()
{
	MGR_SCENE->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = mpBackBuffer->GetMemDC();

	MGR_SCENE->Render(hBackBufferDC);

	mpBackBuffer->Render(hdc);
}

void MainGame::Release()
{
	MGR_SCENE->Release();
	MGR_IMAGE->Release();

	GdiplusShutdown(g_gpToken);
}