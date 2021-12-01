#pragma once
#include "Scene.h"

class Button;
class BmpImage;
class DemonSlayer;
class CharacterSelectScene : public Scene
{
public:
	virtual ~CharacterSelectScene() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void StartGame();
	void ShutdownGame();
	void CreateCharacter();
	void DeleteCharacter();
private:
	BmpImage* backgroundImage = nullptr;
	Image* characterSlotImage = nullptr;
	Image* slotBackgroundImage = nullptr;
	Image* slotFloorImage = nullptr;
	Button* createCharacterButton = nullptr;
	Button* deleteCharacterButton = nullptr;
	Button* shutdownButton = nullptr;
	Button* startButton = nullptr;

	DemonSlayer* myCharacter = nullptr;

	const int buttonSenter = WIN_SIZE_Y - 50;
	const int smallButtonSizeX = 80;
	const int smallButtonSizeY = 30;
	const int largeButtonSizeX = 220;
	const int largeButtonSizeY = 60;

	const int createButtonPosX = WIN_SIZE_X_HALF - 245;
	const int deleteButtonPosX = WIN_SIZE_X_HALF - 160;
	const int shutdownButtonPosX = WIN_SIZE_X_HALF + 160;
	const int startButtonPosX = WIN_SIZE_X_HALF;

	const float buttonStringSenter = buttonSenter - 6.0f;
	const float createStringPosX = createButtonPosX - 32.0f;
	const float deleteStringPosX = deleteButtonPosX - 32.0f;
	const float shutdownStringPosX = shutdownButtonPosX - 26.0f;
	const float startStringPosX = WIN_SIZE_X_HALF - 47.0f;
	const float startStringPosY = buttonStringSenter - 12.0f;
	const float startKeyStringPosX = WIN_SIZE_X_HALF - 20.0f;
	const float startKeyStringPosY = startStringPosY + 24.0f;
};
