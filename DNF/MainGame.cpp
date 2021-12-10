#include "stdafx.h"
#include "MainGame.h"

#include "Timer.h"
#include "SceneManager.h"

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

MainGame::~MainGame() noexcept
{
    DeleteObject(_backBitmap);
    DeleteDC(_backDC);
    ReleaseDC(_hWnd, _hDC);
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

    _hDC = GetDC(_hWnd);
    _backDC = CreateCompatibleDC(_hDC);
    _backBitmap = CreateCompatibleBitmap(_hDC, _res.Width, _res.Height);
    SelectObject(_backDC, _backBitmap);

    Input::Init(_hWnd);
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
    PatBlt(_backDC, 0, 0, _res.Width, _res.Height, WHITENESS);

    SceneManager::GetSingleton()->Render(_backDC);

    BitBlt(_hDC, 0, 0, _res.Width, _res.Height,
        _backDC, 0, 0, SRCCOPY);
}
