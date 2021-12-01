#include "stdafx.h"
#include "Config.h"
#include "TitleScene.h"

HRESULT TitleScene::Init()
{
	titleImage = FROM_FILE(L"Image/TitleScene/Title.png");
	loadingImage = FROM_FILE(L"Image/TitleScene/Loading.png");
	loadingRotateImage = FROM_FILE(L"Image/TitleScene/LoadingRotate.png");
	loadingBelt = FROM_FILE(L"Image/TitleScene/LoadingBelt.png");
	neopleImage = FROM_FILE(L"Image/TitleScene/NeopleImage.png");

	return S_OK;
}

void TitleScene::Update()
{
	const float rotationTime = 0.05f;
	elapsedTime += DELTA_TIME;

	if (elapsedTime > rotationTime)
	{
		rotateAngle += 10.0f;
		elapsedTime -= rotationTime;
	}
}

void TitleScene::Render(HDC hdc)
{
	const int loadingImageSizeX = 210;
	const int loadingImageSizeY = 213;
	const int rotateImageSize = 45;
	const float rotateImageSenter = rotateImageSize * 0.5f;
	const int beltImageSizeX = 45;
	const int neopleImageSizeX = WIN_SIZE_X;
	const int neopleImageSizeY = 34;

	Graphics g(hdc);
	Matrix mt;
	//g.Clear(RGB(0,0,0));

	g.DrawImage(titleImage, 0, 0, WIN_SIZE_X, WIN_SIZE_Y);
	g.DrawImage(loadingBelt, WIN_SIZE_X - beltImageSizeX, WIN_SIZE_Y - 100);
	g.DrawImage(neopleImage, 0, WIN_SIZE_Y - neopleImageSizeY, neopleImageSizeX, neopleImageSizeY);
	g.DrawImage(loadingImage, 690, WIN_SIZE_Y_HALF + loadingImageSizeY, loadingImageSizeX, loadingImageSizeY);

	mt.RotateAt(rotateAngle, PointF(800, 790));
	g.SetTransform(&mt);
	g.DrawImage(loadingRotateImage, 777, 767, rotateImageSize, rotateImageSize);
}

void TitleScene::Release()
{
}
