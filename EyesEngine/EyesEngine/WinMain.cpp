//--------Include-------
#include <stdio.h>
#include <Windows.h>
#include <string>

#include "Game1.h"
#include "../../FW_Stream/FW_Stream/FW_Stream.h"
#include "../../FW_Debug/FW_Debug/FW_Debug.h"
#include "../../FW_Input/FW_Input/FW_Keyboard.h"
//----------------------

using namespace std;

HWND hWnd;
bool windowFullscreen;
int windowHeight, windowWidth;

LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_MULTIPLY)
			PostQuitMessage(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	FW_Debug *m_debug = new FW_Debug();

	FW_Stream *iniStream = new FW_Stream();
	if (m_debug->FW_logs_reset())
		m_debug->FW_success("FW_Debug reset logs file", FW_debugType::LOGS, FW_debugType::NOTHING);
	else
		m_debug->FW_error("FW_Debug reset logs file", FW_debugType::WINDOW, FW_debugType::LOGS);

	//Load option
	if (iniStream->FW_open("option.ini"))
		m_debug->FW_success("FW_Stream load option.ini", FW_debugType::LOGS, FW_debugType::NOTHING);
	else
		m_debug->FW_error("FW_Stram, option.ini error for load", FW_debugType::WINDOW, FW_debugType::LOGS);

	//Window Title
	string windowName = iniStream->FW_search("windowTitle");

	//Window Fullscreen
	int windowFullscreenTemporary = atoi(iniStream->FW_search("fullscreen").c_str());
	windowFullscreen = windowFullscreenTemporary != 0;

	//Window Size
	windowHeight = atoi(iniStream->FW_search("windowHeight").c_str());
	windowWidth = atoi(iniStream->FW_search("windowWidth").c_str());

	if (iniStream->FW_close())
		m_debug->FW_success("FW_Stream unload option.ini", FW_debugType::LOGS, FW_debugType::NOTHING);
	else
		m_debug->FW_warning("FW_Stram unload option.ini", FW_debugType::WINDOW, FW_debugType::LOGS);

	delete iniStream;

	//Init Window
	WNDCLASSEX wndStruct;
	ZeroMemory(&wndStruct, sizeof(WNDCLASSEX));
	wndStruct.cbSize = sizeof(WNDCLASSEX);
	wndStruct.style = CS_HREDRAW | CS_VREDRAW;
	wndStruct.lpfnWndProc = (WNDPROC)wndProc;
	wndStruct.hInstance = hInstance;
	wndStruct.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndStruct.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndStruct.lpszClassName = TEXT("Window");
	RegisterClassEx(&wndStruct);

	if (windowFullscreen)
	{
		hWnd = CreateWindow("Window",
			windowName.c_str(),
			WS_EX_TOPMOST | WS_POPUP,
			0, 0,
			windowWidth,
			windowHeight,
			NULL,
			NULL,
			hInstance,
			NULL);
	}
	else
	{
		hWnd = CreateWindow("Window",
			windowName.c_str(),
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, //WS_OVERLAPPEDWINDOW
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowWidth,
			windowHeight,
			NULL,
			NULL,
			hInstance,
			NULL);
	}

	if (!hWnd)
	{
		m_debug->FW_error("WinMain: CreateWindow", FW_debugType::WINDOW, FW_debugType::LOGS);
		return false;
	}

	delete m_debug;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return true;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	if (!InitWindow(hInstance, nCmdShow))
		return 0;

	Game1 gameMain;
	FW_Debug debug;

	//Mouse cursor
	POINT cursorPos;

	//Initialize
	gameMain.Game_initialized(hWnd, hInstance, windowFullscreen, windowHeight, windowWidth);
	gameMain.Game_loadContent();

	//Mouse - Cursor
	RECT r;
	GetWindowRect(hWnd, &r);
	ShowCursor(FALSE);

	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		float screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
		float screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

		GetCursorPos(&cursorPos);
		//ScreenToClient(hWnd, &cursorPos); //Get Mouse position in Window

		cursorPos.x -= r.left + (windowWidth / 2);
		cursorPos.y -= r.left + (windowHeight / 2);
		SetCursorPos(r.left + (windowWidth / 2), r.left + (windowHeight / 2));

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		gameMain.Game_loop(cursorPos.x, cursorPos.y, screenWidth, screenHeight);
	}

	return (int)msg.wParam;
}

