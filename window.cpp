#include "window.h"

#include <windowsx.h>
#include <WinUser.h>
#include <wingdi.h>


bool Window::init(HINSTANCE hInstance)
{
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	this->width = width;
	this->height = height;

	this->centerX = width / 2;
	this->centerY = height / 2;

	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "Direct3D9App";

	if (!RegisterClass(&wc))
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}

	HWND hwnd = 0;
	hwnd = ::CreateWindow("Direct3D9App",
		"Virtual Billiard",
		WS_POPUP,
		0, 0, width, height,
		0 /*parent hwnd*/, 0 /* menu */, hInstance, 0 /*extra*/);

	if (!hwnd)
	{
		::MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}

	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);


	this->hwnd = hwnd;

	return true;
}

void Window::destory()
{
	ClipCursor(NULL);
}

LRESULT CALLBACK WndProc(
	HWND hwnd, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam
)
{
	Window& window = Window::getInstance();
	static enum { WORLD_MOVE, LIGHT_MOVE, BLOCK_MOVE } move = WORLD_MOVE;

	switch (msg) {
	case WM_DESTROY:
	{
		::PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam) {
		case VK_ESCAPE:
			::DestroyWindow(hwnd);
			break;
		case VK_RETURN:
			window.key[RETURN] = true;
			break;
		case VK_SPACE:
			window.key[SPACE] = true;
			break;
		case 'W':
			window.key[KEY_W] = true;
			break;
		case 'A':
			window.key[KEY_A] = true;
			break;
		case 'S':
			window.key[KEY_S] = true;
			break;
		case 'D':
			window.key[KEY_D] = true;
			break;
		}
		break;
	}
	case WM_KEYUP:
	{
		switch (wParam) {
		case VK_SPACE:
			window.key[SPACE] = false;
			break;
		case 'W':
			window.key[KEY_W] = false;
			break;
		case 'A':
			window.key[KEY_A] = false;
			break;
		case 'S':
			window.key[KEY_S] = false;
			break;
		case 'D':
			window.key[KEY_D] = false;
			break;
		}
		break;
	}

	case WM_MOUSEMOVE:
	{
		
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		window.mouse_dx = window.centerX - x;
		window.mouse_dy = window.centerY - y;

		window.mouse_x = x;
		window.mouse_y = y;

		window.mouse[LEFT] = LOWORD(wParam) & MK_LBUTTON;
		window.mouse[RIGHT] = LOWORD(wParam) & MK_RBUTTON;
		break;
	}
	}

	SetCursorPos(window.centerX, window.centerY);

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}