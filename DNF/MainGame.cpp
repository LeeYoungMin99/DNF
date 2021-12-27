#include "stdafx.h"
#include "MainGame.h"

#include "Timer.h"
#include "SceneManager.h"
#include "ImageManager.h"

ID2D1HwndRenderTarget* gpRenderTarget = nullptr;
IWICImagingFactory* gpImagingFactory = nullptr;
ID2D1HwndRenderTarget* gpTextRenderTarget = nullptr;

LRESULT MainGame::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

MainGame::~MainGame() 
{
}

bool MainGame::Init(HINSTANCE hInst)
{
	LoadStringW(hInst, IDS_APP_TITLE, _title, MAX_LOADSTRING);
	LoadStringW(hInst, IDC_BASICGAMEFRAMEWORK, _windowName, MAX_LOADSTRING);

	_hInst = hInst;

	if (0 == registerClass())
	{
		return false;
	}

	_hWnd = CreateWindowW(_windowName, _title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

	if (_hWnd == NULL)
	{
		return false;
	}

	RECT cr = { 0, 0, _res.Width, _res.Height };
	AdjustWindowRect(&cr, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(_hWnd, HWND_TOPMOST, 100, 100, cr.right - cr.left, cr.bottom - cr.top, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(_hWnd, SW_SHOW);
	UpdateWindow(_hWnd);

	ID2D1Factory* pFactory = nullptr;

	GetClientRect(_hWnd, &cr);
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);

	pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(_hWnd, D2D1::SizeU(cr.right - cr.left, cr.bottom - cr.top)),
		&gpRenderTarget);

	CoInitialize(nullptr);
	CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&gpImagingFactory));

	Input::Init(_hWnd);
	ImageManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	return true;
}

INT32 MainGame::Run()
{
	Timer::Init();

	MSG msg;

	while (TRUE)
	{
		if (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (SceneManager::GetSingleton()->IsSetNextScene())
			{
				SceneManager::GetSingleton()->ChangeScene();
			}

			if (Timer::CanUpdate())
			{
				processInput();
				update();
				render();
			}
		}
	}

	return static_cast<INT32>(msg.wParam);
}

ATOM MainGame::registerClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _hInst;
	wcex.hIcon = LoadIcon(_hInst, MAKEINTRESOURCE(IDI_BASICGAMEFRAMEWORK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _windowName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

void MainGame::processInput()
{
	Input::Update();
}

void MainGame::update()
{
	SceneManager::GetSingleton()->Update();
}

void MainGame::render()
{
	gpRenderTarget->BeginDraw();

	gpRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	SceneManager::GetSingleton()->Render();

	gpRenderTarget->EndDraw();
}
