#pragma once
#pragma comment(lib, "comctl32.lib")
#include <windows.h>
#include <CommCtrl.h>
#include "Paint.h"



LRESULT CALLBACK Main_WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Field_WndProc(HWND, UINT, WPARAM, LPARAM);

class Window
{
public:
	Window();
	~Window();

	bool Create_App(HINSTANCE hInst);
	MSG* Get_MSG();

	void case_WM_CREATE(HWND hWnd);
	void case_WM_SIZE();
	void case_WM_PAINT_main_window();
	void case_WM_PAINT_field_window();
	void case_WM_COMMAND(WPARAM wparam);
	void case_WM_CLOSE();
	void case_WM_RBUTTONDOWN(LPARAM lparam);
	void case_WM_LBUTTONDOWN(LPARAM lparam);
	void case_WM_MOUSEMOVE(LPARAM lparam);
	void case_WM_LBUTTONUP(LPARAM lparam);
	void case_WM_RBUTTONUP(LPARAM lparam);

private:
	bool create_main_window();
	bool create_field_window(HWND hWnd_Main);
	bool create_toolbar(HWND hWndParent);

	void draw_screen(HDC hDc, PAINTSTRUCT& pstr);

	HINSTANCE	hInst;
	HWND		hWnd_Main,
				hField,
				hWndToolbar;
	HDC			hDc;
	PAINTSTRUCT pstr;
	MSG			msg;
	WNDCLASSEX	wc;
	RECT		rect;

	Paint PAINT;

	HPEN hZero_Pen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	HBRUSH hWhite_Brush = CreateSolidBrush(RGB(255, 255, 255));
};

