// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#ifdef _DEBUG
#include <crtdbg.h>
#endif

// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <string>
#include <type_traits>

#include "Type.h"
#include "Singleton.h"
#include "Macro.h"
#include "Input.h"
#include "Timer.h"

#include <json/json.h>
#ifdef _DEBUG
#pragma comment(lib,"jsoncppd.lib")
#else
#pragma comment(lib,"jsoncpp.lib")
#endif

// imaingFactory 생성을 위한 include
#include <dwrite_3.h>
#include <wincodec.h>

#include <dwrite.h>

// Direct2D를 쓰기 위해서 필요한 헤더
#include <d2d1.h>
// C++에서 유용한 함수들, 클래스들이 정의
#include <d2d1helper.h>
// 점, 선 또는 사각형같은 기본적인 그리기에 대한 정보가 정의
#include <d2dbasetypes.h>
// Direct2D에서 사용하는 에러코드가 정의되어있음.
#include <d2derr.h>
// Direct2D에서 기본 제공하는 이펙트가 있음
#include <d2d1effects.h>
extern ID2D1HwndRenderTarget* gpRenderTarget;
extern IWICImagingFactory* gpImagingFactory;

// 전처리문
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

using namespace std;
using namespace std::chrono;