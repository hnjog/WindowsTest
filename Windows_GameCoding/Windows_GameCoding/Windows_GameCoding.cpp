// Windows_GameCoding.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include"pch.h"
#include "framework.h"
#include "Windows_GameCoding.h"
#include "Game.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 얘네 아무 의미 없음 -> 일종의 주석
	// 그냥 컴파일 용임 (호환용?)
	/*UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);*/

	// 전역 문자열을 초기화합니다.
	// 고정 값으로 할것이라면 필요 없음
	/*LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSGAMECODING, szWindowClass, MAX_LOADSTRING);*/

	// 1. 윈도우 창 정보 등록
	MyRegisterClass(hInstance);

	// 2. 윈도우 창 생성
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	Game game;
	game.Init(g_hWnd);

	MSG msg = {};
	uint64 prevTick = 0;

	// 3. 메인 루프
	// 입력 -> 로직 -> 렌더링
	//::GetMessage(&msg, nullptr, 0, 0)
	while (msg.message != WM_QUIT)
	{
		// msg 존재시 게임 로직 말고 입력 처리
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// :: 를 붙임으로서 windows나 공식적으로 지원되는 함수라는 표현
			// msg 처리를 통해 입력, 로직을 처리
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			uint64 now = ::GetTickCount64();

			// 프레임이 너무 늘어나는 것을 막을 수 있음
			//if (now - prevTick >= 10)
			{
				// Game Logic 
				game.Update();
				game.Render();

				prevTick = now;
			}

		}
	}

	return (int)msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc; // func Pointer
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSGAMECODING));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINDOWSGAMECODING);
	wcex.lpszClassName = L"GameCoding";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.


	RECT windowRect = { 0,0,800,600 };
	::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	// 실질적인 '창'을 만들어준다
	HWND hWnd = CreateWindowW(L"GameCoding", L"Client", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, hInstance, nullptr);

	g_hWnd = hWnd;

	if (!hWnd)
	{
		return FALSE;
	}

	::ShowWindow(hWnd, nCmdShow);
	::UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		// -> 내부적으로는 정수하나와 비슷하다
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

		//문자
		/*WCHAR buffer[100];
		::TextOut(hdc, 100, 100, buffer, ::wcslen(buffer));*/

		// 사각형
		//::Rectangle(hdc, 200, 200, 400, 400);
		//// 원
		//::Ellipse(hdc, 200, 200, 400, 400);
		//// 선
		//::MoveToEx(hdc, 300, 300, nullptr);
		//::LineTo(hdc, 400, 400);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_MOUSEMOVE:
	{
		//::InvalidateRect(hWnd, nullptr, TRUE);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
