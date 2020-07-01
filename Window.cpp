#include "Window.h"


#define TOOL_BAR_SIZE_Y 30
//
#define IDM_OPEN	101
#define IDM_SAVE	102
#define IDM_UNDO	103
#define IDM_BOND	104
#define IDM_HAND	105
#define IDM_TRGL	106
#define IDM_RECT	107
#define IDM_CRCL	108
#define IDM_DELT	109
#define IDM_BOX		110
#define IDM_LINE	111
//
#define IDM_FIELD	900


Window::Window()
{
}

Window::~Window()
{
}

bool Window::Create_App(HINSTANCE hInst)
{
	this->hInst = hInst;
	if (!create_main_window())
	{
		MessageBoxA(NULL, "Something went wrong while creating the main window!", "Warning!", MB_OK);
		return false;
	}
	else
		ShowWindow(hWnd_Main, 1);
	return true;
}

MSG* Window::Get_MSG()
{
	return &msg;
}

void Window::case_WM_CREATE(HWND hWnd)
{
	if (!create_field_window(hWnd))
	{
		MessageBoxA(NULL, "Something went wrong while creating the 'field_window'!", "Warning!", MB_OK);
	}
	if (!create_toolbar(hWnd))
	{
		MessageBoxA(NULL, "Something went wrong while creating the 'tool_bar'!", "Warning!", MB_OK);
	}
}

void Window::case_WM_SIZE()
{
	GetClientRect(hWnd_Main, &rect);
	MoveWindow(hField, 0, TOOL_BAR_SIZE_Y, rect.right, rect.bottom, true);
	SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
}

void Window::case_WM_PAINT_main_window()
{
	hDc = BeginPaint(hWnd_Main, &pstr);
	EndPaint(hWnd_Main, &pstr);
}

void Window::case_WM_PAINT_field_window()
{
	hDc = BeginPaint(hField, &pstr);

	draw_screen(hDc, pstr);

	EndPaint(hField, &pstr);
}

void Window::case_WM_COMMAND(WPARAM wparam)
{
	switch (LOWORD(wparam))
	{
	case IDM_OPEN:
		PAINT.Open_button(hWnd_Main);
		break;
	case IDM_SAVE:
		PAINT.Save_button(hWnd_Main);
		break;
	case IDM_UNDO:
		break;
	case IDM_DELT:
		PAINT.Tool_select(tool_DELT);
		break;
	case IDM_BOND:
		PAINT.Tool_select(tool_BOND);
		break;
	case IDM_BOX:
		PAINT.Tool_select(tool_BOX);
		break;
	case IDM_HAND:
		PAINT.Tool_select(tool_HAND);
		break;
	case IDM_TRGL:
		PAINT.Tool_select(tool_TRGL);
		break;
	case IDM_RECT:
		PAINT.Tool_select(tool_RECT);
		break;
	case IDM_CRCL:
		PAINT.Tool_select(tool_CRCL);
		break;
	case IDM_LINE:
		PAINT.Tool_select(tool_LINE);
		break;
	}
}

void Window::case_WM_CLOSE()
{
	int choise = MessageBoxA(NULL, "Do you want to save the changes?", "Warning!", MB_YESNOCANCEL);
	switch (choise)
	{
	case IDYES:
		PAINT.Save_button(hWnd_Main);
	case IDNO:
		DestroyWindow(hWnd_Main);
		break;
	case IDCANCEL:
		break;
	}
}

void  Window::case_WM_RBUTTONDOWN(LPARAM lparam)
{
	PAINT.Right_button_down(hField, lparam);
}

void  Window::case_WM_LBUTTONDOWN(LPARAM lparam)
{
	PAINT.Left_button_down(hField, lparam);
}

void  Window::case_WM_MOUSEMOVE(LPARAM lparam)
{
	PAINT.Mouse_move(hField, lparam);
}

void  Window::case_WM_LBUTTONUP(LPARAM lparam)
{
	PAINT.Left_button_up(hField, lparam);
}

void  Window::case_WM_RBUTTONUP(LPARAM lparam)
{
	PAINT.Right_button_up(hField, lparam);
}

bool Window::create_main_window()
{
	RECT rect = { 0, 0, 600, 300 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(108));
	wc.hInstance = hInst;
	wc.lpfnWndProc = Main_WndProc;
	wc.lpszClassName = "Main_Class";

	RegisterClassEx(&wc);

	hWnd_Main = CreateWindow(	"Main_Class",
								"SuperPaint",
								WS_OVERLAPPEDWINDOW,
								NULL, NULL,
								rect.right - rect.left, rect.bottom - rect.top,
								NULL,
								NULL,
								hInst,
								NULL);

	if (!hWnd_Main)
	{
		return false;
	}
	return true;
}

bool Window::create_field_window(HWND hWnd_Main)
{
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = Field_WndProc;
	wc.lpszClassName = "Field_Class";

	RegisterClassEx(&wc);

	hField = CreateWindow("Field_Class",
		NULL,
		WS_OVERLAPPED | WS_CHILD,
		0, TOOL_BAR_SIZE_Y,
		0, 0,
		hWnd_Main,
		(HMENU)IDM_FIELD,
		hInst,
		NULL);

	if (!hField)
	{
		return false;
	}

	ShowWindow(hField, 1);
	return true;
}

bool Window::create_toolbar(HWND hWnd_Main)
{
	const int numButtons = 12;
	const int bitmapSize = 16;

	const DWORD buttonStyles = BTNS_AUTOSIZE;

	hWndToolbar = CreateWindow(TOOLBARCLASSNAME,
		NULL,
		WS_CHILD | TBSTYLE_WRAPABLE,
		0, 0, 0, 0,
		hWnd_Main,
		NULL,
		hInst,
		NULL);
	if (hWndToolbar == NULL)
		return false;

	HIMAGELIST hImageList = ImageList_Create(bitmapSize, bitmapSize,
		ILC_COLOR16 | ILC_MASK,
		numButtons, 0);

	ImageList_Add(hImageList, LoadBitmap(hInst, MAKEINTRESOURCE(106)), NULL);

	SendMessage(hWndToolbar, TB_SETIMAGELIST, NULL, (LPARAM)hImageList);

	TBBUTTON tbButtons[numButtons] =
	{
		{ 0, IDM_RECT, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, 0 },
		{ 1, IDM_CRCL, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, 0 },
		{ 2, IDM_TRGL, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, 0 },
		{ 3, IDM_LINE, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, 0 },
		{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0 },
		{ 4, IDM_BOX,  TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, 0 },
		{ 5, IDM_BOND, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, 0 },
		{ 6, IDM_HAND, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, 0 },
		{ 7, IDM_DELT, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, 0 },
		{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0 },
		{ 8, IDM_OPEN, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, 0 },
		{ 9, IDM_SAVE, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, 0 }
	};

	SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hWndToolbar, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)&tbButtons);

	ShowWindow(hWndToolbar, TRUE);

	return true;
}

void Window::draw_screen(HDC hDc, PAINTSTRUCT& pstr)
{
	HBITMAP temp_bitmap = CreateCompatibleBitmap(hDc, pstr.rcPaint.right, pstr.rcPaint.bottom);
	HDC hDcSource = CreateCompatibleDC(hDc);

	SelectObject(hDcSource, temp_bitmap);
	SelectObject(hDcSource, hZero_Pen);
	SelectObject(hDcSource, hWhite_Brush);
	Rectangle(hDcSource, 0, 0, pstr.rcPaint.right, pstr.rcPaint.bottom);

	PAINT.Draw(hDcSource);

	StretchBlt(hDc, 0, 0, pstr.rcPaint.right, pstr.rcPaint.bottom,
		hDcSource, 0, 0, pstr.rcPaint.right, pstr.rcPaint.bottom,
		SRCCOPY);

	DeleteObject(temp_bitmap);
	DeleteDC(hDcSource);
}