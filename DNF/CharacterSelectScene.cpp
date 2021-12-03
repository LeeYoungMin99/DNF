#include "stdafx.h"
#include "CharacterSelectScene.h"
#include "Button.h"
#include "DemonSlayer.h"
#include "BmpImage.h"

HRESULT CharacterSelectScene::Init()
{
	mpSlotBackgroundImage = FROM_FILE(L"Image/CharacterSelectScene/SlotBackgroundImage.png");
	mpSlotFloorImage = FROM_FILE(L"Image/CharacterSelectScene/SlotFloorImage.png");

	mpBackgroundImage = new BmpImage;
	mpBackgroundImage->Init("Image/CharacterSelectScene/BackgroundImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	mpCreateCharacterButton = new Button(this, &CharacterSelectScene::CreateCharacter);
	mpDeleteCharacterButton = new Button(this, &CharacterSelectScene::DeleteCharacter);
	mpStartButton = new Button(this, &CharacterSelectScene::StartGame);
	mpShutdownButton = new Button(this, &CharacterSelectScene::ShutdownGame);

	mpCreateCharacterButton->Init(Button::eButtonType::Small, POINT{ CREATE_BUTTON_POS_X,BUTTON_CENTER }, SMALL_BUTTON_SIZE_X, SMALL_BUTTON_SIZE_Y);
	mpDeleteCharacterButton->Init(Button::eButtonType::Small, POINT{ DELETE_BUTTON_POS_X,BUTTON_CENTER }, SMALL_BUTTON_SIZE_X, SMALL_BUTTON_SIZE_Y);
	mpStartButton->Init(Button::eButtonType::Large, POINT{ START_BUTTON_POS_X,BUTTON_CENTER }, LARGE_BUTTON_SIZE_X, LARGE_BUTTON_SIZE_Y);
	mpShutdownButton->Init(Button::eButtonType::Small, POINT{ SHUTDOWN_BUTTON_POS_X,BUTTON_CENTER }, SMALL_BUTTON_SIZE_X, SMALL_BUTTON_SIZE_Y);
	mpMyCharacter = new DemonSlayer;
	mpMyCharacter->Init();

	return S_OK;
}


void CharacterSelectScene::Update()
{
	SAFE_UPDATAE(mpMyCharacter);
	SAFE_UPDATAE(mpCreateCharacterButton);
	SAFE_UPDATAE(mpDeleteCharacterButton);
	SAFE_UPDATAE(mpStartButton);
	SAFE_UPDATAE(mpShutdownButton);
}

void CharacterSelectScene::Render(HDC hdc)
{
	Graphics g(hdc);
	Font fontSmallButton(L"gasinamuM", 8);
	Font fontLargeButton(L"UttumBatangBold", 15, FontStyleBold);
	SolidBrush b(Color(170, 134, 77));

	mpBackgroundImage->Render(hdc, WIN_SIZE_X_HALF, WIN_SIZE_Y_HALF);
	g.DrawImage(mpSlotBackgroundImage, 0, WIN_SIZE_Y_HALF);
	for (int i = 0; i < 7; ++i)
		g.DrawImage(mpSlotFloorImage, (WIN_SIZE_X / 7) * i + 30, WIN_SIZE_Y - 200, 150, 51);

	mpCreateCharacterButton->Render(hdc);
	mpDeleteCharacterButton->Render(hdc);
	mpStartButton->Render(hdc);
	mpShutdownButton->Render(hdc);

	mpMyCharacter->Render(hdc);

	g.DrawString(L"캐릭터생성", -1, &fontSmallButton, PointF(CREATE_STRING_POS_X, BUTTON_STRING_CENTER), &b);
	g.DrawString(L"캐릭터삭제", -1, &fontSmallButton, PointF(DELETE_STRING_POS_X, BUTTON_STRING_CENTER), &b);
	g.DrawString(L"게임시작", -1, &fontLargeButton, PointF(START_STRING_POS_X, START_STRING_POS_Y), &b);
	g.DrawString(L"(Space)", -1, &fontSmallButton, PointF(START_KET_STRING_POS_X, START_KET_STRING_POS_Y), &b);
	g.DrawString(L"게임종료", -1, &fontSmallButton, PointF(SHUTDOWN_STRING_POS_X, BUTTON_STRING_CENTER), &b);
}

void CharacterSelectScene::Release()
{
	SAFE_RELEASE(mpBackgroundImage);
	SAFE_RELEASE(mpMyCharacter);
	SAFE_RELEASE(mpCreateCharacterButton);
	SAFE_RELEASE(mpDeleteCharacterButton);
	SAFE_RELEASE(mpStartButton);
	SAFE_RELEASE(mpShutdownButton);
}

void CharacterSelectScene::StartGame()
{
	MGR_SCENE->ChangeScene(SCENE_TAG::SeriaRoomScene);
}

void CharacterSelectScene::ShutdownGame()
{
	cout << "게임 종료 할거임!!!" << endl;
}

void CharacterSelectScene::CreateCharacter()
{
	MGR_SCENE->ChangeScene(SCENE_TAG::TitleScene);
}

void CharacterSelectScene::DeleteCharacter()
{
	cout << "캐릭터 삭제 할거임!!!" << endl;
}
