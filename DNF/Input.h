#pragma once

#include <Windows.h>

class Input
{
public:
	Input() = delete;
	~Input() = delete;

	static void		Init(HWND hWnd) ;
	static void		Update() ;

	static bool		GetButton(BYTE vkey) ;
	static bool		GetButtonDown(BYTE vkey) ;
	static bool		GetButtonUp(BYTE vkey) ;

	static POINT	GetMousePosition() ;
private:
	static bool		_currentKeyStates[256];
	static bool		_prevKeyStates[256];
	static POINT	_mousePosition;
	static HWND		_hWnd;
};

