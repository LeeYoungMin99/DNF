#pragma once

#include "Type.h"

class MainGame
{
	enum { MAX_LOADSTRING = 100 };

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	~MainGame();

	bool				Init(HINSTANCE hInst);
	INT32				Run();

private:
	ATOM				registerClass();

	void				processInput();
	void				update();
	void				render();
private:
	HINSTANCE			_hInst = {};
	HWND				_hWnd = {};
	WCHAR				_title[MAX_LOADSTRING] = {};
	WCHAR				_windowName[MAX_LOADSTRING] = {};

	Resolution			_res = { 1067, 600 };
};

