#pragma once
#include "Scene.h"

template <typename T>
class Button;

class BmpImage;
class DemonSlayer;
class CharacterSelectScene : public Scene
{
	using Button = Button<CharacterSelectScene>;

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
	BmpImage* mpBackgroundImage = nullptr;
	Image* mpCharacterSlotImage = nullptr;
	Image* mpSlotBackgroundImage = nullptr;
	Image* mpSlotFloorImage = nullptr;
	Button* mpCreateCharacterButton = nullptr;
	Button* mpDeleteCharacterButton = nullptr;
	Button* mpShutdownButton = nullptr;
	Button* mpStartButton = nullptr;

	DemonSlayer* mpMyCharacter = nullptr;

	const int BUTTON_CENTER = WIN_SIZE_Y - 50;
	const int SMALL_BUTTON_SIZE_X = 80;
	const int SMALL_BUTTON_SIZE_Y = 30;
	const int LARGE_BUTTON_SIZE_X = 220;
	const int LARGE_BUTTON_SIZE_Y = 60;

	const int CREATE_BUTTON_POS_X = WIN_SIZE_X_HALF - 245;
	const int DELETE_BUTTON_POS_X = WIN_SIZE_X_HALF - 160;
	const int SHUTDOWN_BUTTON_POS_X = WIN_SIZE_X_HALF + 160;
	const int START_BUTTON_POS_X = WIN_SIZE_X_HALF;

	const float BUTTON_STRING_CENTER = BUTTON_CENTER - 6.0f;
	const float CREATE_STRING_POS_X = CREATE_BUTTON_POS_X - 32.0f;
	const float DELETE_STRING_POS_X = DELETE_BUTTON_POS_X - 32.0f;
	const float SHUTDOWN_STRING_POS_X = SHUTDOWN_BUTTON_POS_X - 26.0f;
	const float START_STRING_POS_X = WIN_SIZE_X_HALF - 47.0f;
	const float START_STRING_POS_Y = BUTTON_STRING_CENTER - 12.0f;
	const float START_KET_STRING_POS_X = WIN_SIZE_X_HALF - 20.0f;
	const float START_KET_STRING_POS_Y = START_STRING_POS_Y + 24.0f;
};
