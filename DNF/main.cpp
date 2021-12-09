// main.cpp

#include "stdafx.h"
#include "MainGame.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

void jsonWrite()
{
	ofstream json_file;
	json_file.open("d:\\JSON_DATA.json");

	Json::Value Computer;
	Computer["CPU"] = "I7";
	Computer["RAM"] = "16G";

	Json::Value Language;
	Language["C++"] = "Visual Studio";
	Language["Python"] = "IDLE";

	Computer["Program"] = Language;
	Computer["HDD"] = "2TB";

	Json::Value Cable;
	Cable.append("Power");
	Cable.append("Printer");
	Cable.append("Mouse");

	Computer["Computer"]["Cable"] = Cable;

	Json::Value number;
	number["Int"] = 123;
	number["Double"] = 456.012;
	number["Bool"] = true;

	Computer["Computer"]["Number"] = number;

	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "		"; // Tab
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	writer->write(Computer, &cout);
	writer->write(Computer, &json_file);
	cout << endl;	// add if and flush

	json_file.close();
}

void jsonRead() {
	ifstream json_dir("d:\\JSON_DATA.json");
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	Json::Value value; JSONCPP_STRING errs;
	bool ok = parseFromStream(builder, json_dir, &value, &errs);
	if (ok == true) {
		cout << "CPU: " << value["CPU"] << endl;
		cout << "Program Python: " << value["Program"]["Python"] << endl;
		cout << "Computer Cable: " << value["Computer"]["Cable"] << endl;
		cout << "Computer Cable[0]: " << value["Computer"]["Cable"][0] << endl;
		cout << endl;
		cout << "Computer Number Int(as int): " << value["Computer"]["Number"].get("Int", -1).asInt() << endl; // "Int" ���� ������ -1 ��ȯ. 
		cout << "Computer Number Int(as int): " << value["Computer"]["Number"]["Int"].asInt() << endl; // "Int" ���� ������ 0 ��ȯ. 
		cout << "Computer Number Double(as double): " << value["Computer"]["Number"].get("Double", -1).asDouble() << endl; // "Double" ���� ������ -1 ��ȯ. 
		cout << "Computer Number Double(as string): " << value["Computer"]["Number"].get("Double", "Empty").asString() << endl; // "Double" ���� ������ Empty ��ȯ. 
		cout << "Computer Number Bool(as bool): " << value["Computer"]["Number"].get("Bool", false).asBool() << endl; // "Bool" ���� ������ false ��ȯ. 
		cout << endl; cout << "Root size: " << value.size() << endl;
		cout << "Program size: " << value["Program"].size() << endl;
		cout << "Computer Cable size: " << value["Computer"]["Cable"].size() << endl;
		cout << endl; int size = value["Computer"]["Cable"].size(); // size() ���� for ������ �״�� ���ϸ� warning C4018�� �߻� �Ѵ�.
		for (int i = 0; i < size; i++)
			cout << "Computer Cable: " << value["Computer"]["Cable"][i] << endl;
		cout << endl;
		for (auto i : value["Computer"]["Cable"])
			cout << "Computer Cable: " << i << endl;
	}
	else
	{
		cout << "Parse failed." << endl;
	}
}



// ��������
HINSTANCE	g_hInstance;
HWND		g_hWnd;
LPWSTR		g_lpszClass = (LPWSTR)TEXT("DNF");
MainGame	g_mainGame;

GdiplusStartupInput g_gpsi;
ULONG_PTR g_gpToken;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance,
	_In_ LPWSTR _lpszCmdParam, _In_ int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	//_CrtSetBreakAlloc(273);

	// �����츦 �����ϱ� ���� �⺻ ����
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = NULL;
	wndClass.cbWndExtra = NULL;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // �ڵ�����ȯ
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = _hInstance;
	wndClass.lpfnWndProc = WndProc;				// �Լ�������(�ݹ��Լ�)
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = g_lpszClass;
	wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;	// bit����

	// ������ Ŭ���� ���
	RegisterClass(&wndClass);

	// ������ ����
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW,
		WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y,
		NULL, NULL, _hInstance, NULL);

	RECT cr = { 0, 0, WIN_SIZE_X, WIN_SIZE_Y };
	AdjustWindowRect(&cr, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(g_hWnd, HWND_TOPMOST, 100, 100, cr.right - cr.left, cr.bottom - cr.top, SWP_NOMOVE | SWP_NOZORDER);

	// ���ΰ��� �ʱ�ȭ
	g_mainGame.Init();

	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// �޽��� ť�� �ִ� �޽��� ó��
	MSG message;

	HDC hdc;
	PAINTSTRUCT ps;

	printf("Json ���� ����\n");
	jsonWrite();
	printf("\n\nJson ���� �б�\n");
	jsonRead();

	while (TRUE)
	{
		if (PeekMessage(&message, nullptr, NULL, NULL, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			if (Timer::CanUpdate())
			{
				Input::Update();
				g_mainGame.Update();

				hdc = BeginPaint(g_hWnd, &ps);
				g_mainGame.Render(hdc);
				EndPaint(g_hWnd, &ps);
			}
		}
	}

	// ���ΰ��� ����
	g_mainGame.Release();
	return (int)(message.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	switch (iMessage)
	{
	case WM_DESTROY:	// �ݱ� ��ư �޽���ó�� (���α׷� ����)
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
