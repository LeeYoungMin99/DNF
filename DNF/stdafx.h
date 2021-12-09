#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <list>
#include <queue>
using namespace std;

#pragma comment(lib, "winmm.lib")

#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;

#include "Timer.h"
#include "SceneManager.h"
#include "BmpImageManager.h"
#include "CameraManager.h"
#include "Timer.h"
#include "BmpImage.h"
#include "Input.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern GdiplusStartupInput g_gpsi;
extern ULONG_PTR g_gpToken;

#include <json/json.h>
#ifdef _DEBUG
#pragma comment(lib, "jsoncppd.lib")
#else
#pragma comment(lib, "jsoncpp.lib")
#endif