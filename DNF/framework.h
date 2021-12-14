// header.h: ǥ�� �ý��� ���� ����
// �Ǵ� ������Ʈ Ư�� ���� ������ ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEBUG
#include <crtdbg.h>
#endif

// Windows ��� ����
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
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

// imaingFactory ������ ���� include
#include <dwrite_3.h>
#include <wincodec.h>

#include <dwrite.h>

// Direct2D�� ���� ���ؼ� �ʿ��� ���
#include <d2d1.h>
// C++���� ������ �Լ���, Ŭ�������� ����
#include <d2d1helper.h>
// ��, �� �Ǵ� �簢������ �⺻���� �׸��⿡ ���� ������ ����
#include <d2dbasetypes.h>
// Direct2D���� ����ϴ� �����ڵ尡 ���ǵǾ�����.
#include <d2derr.h>
// Direct2D���� �⺻ �����ϴ� ����Ʈ�� ����
#include <d2d1effects.h>
extern ID2D1HwndRenderTarget* gpRenderTarget;
extern IWICImagingFactory* gpImagingFactory;

// ��ó����
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

using namespace std;
using namespace std::chrono;