#include <windows.h>
#include "Window.h"


Window WINDOW;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdBond, int nShowCmd)
{
	if (!WINDOW.Create_App(hInstance))
		return NULL;

	while (GetMessage(WINDOW.Get_MSG(), NULL, NULL, NULL))
	{
		DispatchMessage(WINDOW.Get_MSG());
	}

	return NULL;
}

LRESULT CALLBACK Main_WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_CREATE:
		WINDOW.case_WM_CREATE(hwnd);
		break;
	case WM_SIZE:
		WINDOW.case_WM_SIZE();
		break;
	case WM_PAINT:
		WINDOW.case_WM_PAINT_main_window();
		break;
	case WM_COMMAND:
		WINDOW.case_WM_COMMAND(wparam);
		break;
	case WM_CLOSE:
		WINDOW.case_WM_CLOSE();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
	return NULL;
}
LRESULT CALLBACK Field_WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static RECT rect;

	switch (message)
	{
	case WM_PAINT:
		WINDOW.case_WM_PAINT_field_window();
		break;
	case WM_RBUTTONDOWN:
		WINDOW.case_WM_RBUTTONDOWN(lparam);
		break;
	case WM_LBUTTONDOWN:
		WINDOW.case_WM_LBUTTONDOWN(lparam);
		break;
	case WM_MOUSEMOVE:
		WINDOW.case_WM_MOUSEMOVE(lparam);
		break;
	case WM_LBUTTONUP:
		WINDOW.case_WM_LBUTTONUP(lparam);
		break;
	case WM_RBUTTONUP:
		WINDOW.case_WM_RBUTTONUP(lparam);
		break;
	default:
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
	return NULL;
}