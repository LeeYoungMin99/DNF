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
#include <string>
#include <type_traits>

#include "Type.h"
#include "Singleton.h"
#include "Macro.h"
#include "Input.h"

#include <json/json.h>
#ifdef _DEBUG
#pragma comment(lib,"jsoncppd.lib")
#else
#pragma comment(lib,"jsoncpp.lib")
#endif

using namespace std;
using namespace std::chrono;