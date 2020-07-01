#pragma once
#include <windows.h>
#include <fstream>
#include <list>

#include "ScreenObj.h"
#include "Rect.h"
#include "Crcl.h"
#include "Trgl.h"
#include "Bond.h"
#include "Box.h"


enum tool { tool_RECT, tool_CRCL, tool_TRGL, tool_LINE, tool_HAND, tool_DELT, tool_BOND, tool_BOX };


class Paint
{
public:
	Paint();
	~Paint();

	void Tool_select(tool choosen_tool);
	void Draw(HDC hDc);

	void Left_button_down(HWND hwnd, LPARAM lparam);
	void Right_button_down(HWND hwnd, LPARAM lparam);
	void Mouse_move(HWND hwnd, LPARAM lparam);
	void Left_button_up(HWND hwnd, LPARAM lparam);
	void Right_button_up(HWND hwnd, LPARAM lparam);

	void Open_button(HWND hwnd);
	void Save_button(HWND hwnd);

private:
	void insert_object();
	void delete_object();
	bool is_object_picked();
	void clear_object_list();
	
	bool in_draw = false;
	bool in_move = false;
	bool in_bond = false;
	bool in_size = false;

	std::fstream f_obj;
	
	RECT rect = { 0 };
	tool choosen_tool = tool_RECT;

	std::list<ScreenObj*> objects_on_screen;
	ScreenObj* object_in_process = NULL;
	ScreenObj* picked_object = NULL;
};

