#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

#pragma comment(lib, "winmm.lib")

#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;

#include "KeyManager.h"
#include "TimerManager.h"
#include "SceneManager.h"
#include "BmpImageManager.h"
#include "CameraManager.h"
#include "Timer.h"
#include "BmpImage.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
extern GdiplusStartupInput g_gpsi;
extern ULONG_PTR g_gpToken;