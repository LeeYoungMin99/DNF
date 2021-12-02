#include "stdafx.h"
#include "Config.h"
#include "TitleScene.h"

HRESULT TitleScene::Init()
{
	mpTitleImage = FROM_FILE(L"Image/TitleScene/Title.bmp");
	mpLoadingImage = FROM_FILE(L"Image/TitleScene/Loading.png");
	mpLoadingRotateImage = FROM_FILE(L"Image/TitleScene/LoadingRotate.png");
	mpLoadingBelt = FROM_FILE(L"Image/TitleScene/LoadingBelt.png");
	mpNeopleImage = FROM_FILE(L"Image/TitleScene/NeopleImage.png");

	return S_OK;
}

void TitleScene::Update()
{
	const float rotationTime = 0.05f;
	mElapsedTime += DELTA_TIME;

	if (mElapsedTime > rotationTime)
	{
		mRotateAngle += 10.0f;
		mElapsedTime -= rotationTime;
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

	g.DrawImage(mpTitleImage, 0, 0);
	g.DrawImage(mpLoadingBelt, WIN_SIZE_X - beltImageSizeX, WIN_SIZE_Y - 100);
	g.DrawImage(mpNeopleImage, 0, WIN_SIZE_Y - neopleImageSizeY, neopleImageSizeX, neopleImageSizeY);
	g.DrawImage(mpLoadingImage, 690, WIN_SIZE_Y_HALF + loadingImageSizeY, loadingImageSizeX, loadingImageSizeY);

	mt.RotateAt(mRotateAngle, PointF(800, 790));
	g.SetTransform(&mt);
	g.DrawImage(mpLoadingRotateImage, 777, 767, rotateImageSize, rotateImageSize);
}

void TitleScene::Release()
{
}
