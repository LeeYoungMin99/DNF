#include "stdafx.h"
#include "CharacterSelectScene.h"
#include "Button.h"
#include "DemonSlayer.h"
#include "BmpImage.h"

HRESULT CharacterSelectScene::Init()
{
	slotBackgroundImage = FROM_FILE(L"Image/CharacterSelectScene/SlotBackgroundImage.png");
	slotFloorImage = FROM_FILE(L"Image/CharacterSelectScene/SlotFloorImage.png");

	backgroundImage = new BmpImage;
	backgroundImage->Init("Image/CharacterSelectScene/BackgroundImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	createCharacterButton = new Button(this, &CharacterSelectScene::CreateCharacter);
	deleteCharacterButton = new Button(this, &CharacterSelectScene::DeleteCharacter);
	startButton = new Button(this, &CharacterSelectScene::StartGame);
	shutdownButton = new Button(this, &CharacterSelectScene::ShutdownGame);

	createCharacterButton->Init(eButtonType::Small, POINT{ createButtonPosX,buttonSenter }, smallButtonSizeX, smallButtonSizeY);
	deleteCharacterButton->Init(eButtonType::Small, POINT{ deleteButtonPosX,buttonSenter }, smallButtonSizeX, smallButtonSizeY);
	startButton->Init(eButtonType::Large, POINT{ startButtonPosX,buttonSenter }, largeButtonSizeX, largeButtonSizeY);
	shutdownButton->Init(eButtonType::Small, POINT{ shutdownButtonPosX,buttonSenter }, smallButtonSizeX, smallButtonSizeY);

	myCharacter = new DemonSlayer;
	myCharacter->Init();

	return S_OK;
}

void CharacterSelectScene::Update()
{
	myCharacter->Update();
	createCharacterButton->Update();
	deleteCharacterButton->Update();
	startButton->Update();
	shutdownButton->Update();
}

void CharacterSelectScene::Render(HDC hdc)
{
	Graphics g(hdc);
	Font fontSmallButton(L"UttumBatangBold", 8);
	Font fontLargeButton(L"UttumBatangBold", 15, FontStyleBold);
	SolidBrush b(Color(170, 134, 77));

	backgroundImage->Render(hdc, WIN_SIZE_X_HALF, WIN_SIZE_Y_HALF);
	g.DrawImage(slotBackgroundImage, 0, WIN_SIZE_Y_HALF);
	for (int i = 0; i < 7; ++i)
		g.DrawImage(slotFloorImage, (WIN_SIZE_X / 7) * i + 30, WIN_SIZE_Y - 200, 150, 51);

	createCharacterButton->Render(hdc);
	deleteCharacterButton->Render(hdc);
	startButton->Render(hdc);
	shutdownButton->Render(hdc);

	myCharacter->Render(hdc);

	g.DrawString(L"캐릭터생성", -1, &fontSmallButton, PointF(createStringPosX, buttonStringSenter), &b);
	g.DrawString(L"캐릭터삭제", -1, &fontSmallButton, PointF(deleteStringPosX, buttonStringSenter), &b);
	g.DrawString(L"게임시작", -1, &fontLargeButton, PointF(startStringPosX, startStringPosY), &b);
	g.DrawString(L"(Space)", -1, &fontSmallButton, PointF(startKeyStringPosX, startKeyStringPosY), &b);
	g.DrawString(L"게임종료", -1, &fontSmallButton, PointF(shutdownStringPosX, buttonStringSenter), &b);
}

void CharacterSelectScene::Release()
{
	SAFE_RELEASE(backgroundImage);
	SAFE_RELEASE(myCharacter);
	SAFE_RELEASE(createCharacterButton);
	SAFE_RELEASE(deleteCharacterButton);
	SAFE_RELEASE(startButton);
	SAFE_RELEASE(shutdownButton);
}

void CharacterSelectScene::StartGame()
{
	cout << "씬 바뀔거임!!!" << endl;
}

void CharacterSelectScene::ShutdownGame()
{
	cout << "게임 종료 할거임!!!" << endl;
}

void CharacterSelectScene::CreateCharacter()
{
	cout << "씬 바뀔거임!!!" << endl;
}

void CharacterSelectScene::DeleteCharacter()
{
	cout << "캐릭터 삭제 할거임!!!" << endl;
}
