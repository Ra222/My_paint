#include "Paint.h"

extern std::unordered_map<int, ScreenObj*> objs;

Paint::Paint()
{
}

Paint::~Paint()
{
	clear_object_list();
}

void Paint::Draw(HDC hDc)
{
	for (auto i = objects_on_screen.rbegin(); i != objects_on_screen.rend(); i++)
		(*i)->Draw(hDc);
	if (in_draw)
		object_in_process->Draw(hDc);
}
//////////////////////////////////////////////////////////////////////
//Button events///////////////////////////////////////////////////////
void Paint::Tool_select(tool choosen_tool)
{
	this->choosen_tool = choosen_tool;
}

void Paint::Left_button_down(HWND hwnd, LPARAM lparam)
{
	rect.left = LOWORD(lparam);
	rect.top = HIWORD(lparam);
	rect.right = LOWORD(lparam);
	rect.bottom = HIWORD(lparam);

	switch (choosen_tool)
	{
	case tool_RECT:
		object_in_process = new Rect(rect, GetTickCount());
		in_draw = true;
		break;
	case tool_CRCL:
		object_in_process = new Crcl(rect, GetTickCount());
		in_draw = true;
		break;
	case tool_TRGL:
		object_in_process = new Trgl(rect, GetTickCount());
		in_draw = true;
		break;
	case tool_LINE:
		object_in_process = new Line(rect, GetTickCount());
		in_draw = true;
		break;
	case tool_BOX:
		object_in_process = new Box(rect, GetTickCount());
		in_draw = true;
		break;
	case tool_BOND:
		if (is_object_picked())
		{
			object_in_process = new Bond(GetTickCount(), picked_object->Get_ID(), 0);
			in_draw = true;
			in_bond = true;
		}
		break;
	case tool_HAND:
		if (is_object_picked())
		{
			object_in_process = picked_object;
			object_in_process->Grab();
			in_move = true;
		}
		break;
	case tool_DELT:
		delete_object();
		break;
	}
}

void Paint::Right_button_down(HWND hwnd, LPARAM lparam)
{
	rect.left = LOWORD(lparam);
	rect.top = HIWORD(lparam);
	rect.right = LOWORD(lparam);
	rect.bottom = HIWORD(lparam);

	switch (choosen_tool)
	{
	case tool_HAND:
		if (in_size = is_object_picked())
			object_in_process = picked_object;
		break;
	}
}

void Paint::Mouse_move(HWND hwnd, LPARAM lparam)
{
	if (object_in_process)
	{	
		rect.right = LOWORD(lparam);
		rect.bottom = HIWORD(lparam);

		if (in_size)
		{
			object_in_process->Scale(rect.right - rect.left, rect.bottom - rect.top);
		}
		else if (in_move)
		{
			object_in_process->Move(rect.right - rect.left, rect.bottom - rect.top);
		}
		else if (in_draw)
		{
			object_in_process->Resize(rect.right, rect.bottom);
		}

		rect.left = LOWORD(lparam);
		rect.top = HIWORD(lparam);

		InvalidateRect(hwnd, NULL, false);
		UpdateWindow(hwnd);
	}
}

void Paint::Left_button_up(HWND hwnd, LPARAM lparam)
{
	if (in_move)
	{
		object_in_process->Release();
	}
	if (in_bond)
	{
		if (is_object_picked())
			object_in_process->Set_end_point(picked_object->Get_ID());
		else
		{
			delete object_in_process;
			in_draw = false;
		}
	}
	if (in_draw)
	{
		if(!IsRectEmpty( &object_in_process->Get_rect() ))
			insert_object();
		else
			delete object_in_process;
	}

	in_size = false;
	in_bond = false;
	in_move = false;
	in_draw = false;
	
	object_in_process = NULL;

	InvalidateRect(hwnd, NULL, false);
	UpdateWindow(hwnd);
}

void Paint::Right_button_up(HWND hwnd, LPARAM lparam)
{
	objects_on_screen.sort([](ScreenObj* a, ScreenObj* b) { return (a->Get_area() < b->Get_area()); });
	in_size = false;

	InvalidateRect(hwnd, NULL, false);
	UpdateWindow(hwnd);
}
//////////////////////////////////////////////////////////////////////
//Open/Save///////////////////////////////////////////////////////////
void Paint::Open_button(HWND hwnd)
{
	OPENFILENAME ofn = { 0 };
	char szFile[512] = { 0 };

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = ("My files(*.mp)\0*.mp\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		f_obj.open(szFile, std::fstream::in | std::fstream::binary);

		if (f_obj.is_open())
		{
			clear_object_list();
			type my_type;

			while (f_obj.read((char*)&my_type, sizeof(my_type)))
			{
				switch (my_type)
				{
				case type_RECT:
					object_in_process = new Rect;
					break;
				case type_CRCL:
					object_in_process = new Crcl;
					break;
				case type_TRGL:
					object_in_process = new Trgl;
					break;
				case type_LINE:
					object_in_process = new Line;
					break;
				case type_BOND:
					object_in_process = new Bond;
					break;
				case type_BOX:
					object_in_process = new Box;
					break;
				}

				if (!object_in_process->Read(f_obj))
				{
					MessageBoxA(NULL, "Error reading file!", "Warning!.", MB_OK);
					clear_object_list();
					break;
				}
				objects_on_screen.push_back(object_in_process);
			}
			f_obj.close();
			objects_on_screen.sort([](ScreenObj* a, ScreenObj* b) { return (a->Get_area() < b->Get_area()); });
		}
		else
		{
			MessageBoxA(NULL, "Error opening file!", "Warning!.", MB_OK);
		}

		InvalidateRect(hwnd, NULL, false);
		UpdateWindow(hwnd);
	}
}

void Paint::Save_button(HWND hwnd)
{
	OPENFILENAME ofn = { 0 };
	char szFile[512] = { 0 };

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = ("My files(*.mp)\0*.mp\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileName(&ofn) == TRUE)
	{
		f_obj.open(szFile, std::fstream::out | std::fstream::binary | std::fstream::trunc);

		if (f_obj.is_open())
		{
			for (auto i = objects_on_screen.begin(); i != objects_on_screen.end(); i++)
			{
				if (!(*i)->Write(f_obj))
				{
					MessageBoxA(NULL, "Error writing file!", "Warning!.", MB_OK);
					f_obj.close();
					return;
				}
			}
			f_obj.close();

			MessageBoxA(NULL, "File saved!", "Notification.", MB_OK);
		}
		else
		{
			MessageBoxA(NULL, "Error saving file!", "Warning!.", MB_OK);
		}
	}
}
//////////////////////////////////////////////////////////////////////
//Support functions///////////////////////////////////////////////////
void Paint::insert_object()
{
	auto i = objects_on_screen.begin();
	for (; i != objects_on_screen.end(); i++)
	{
		if ((*i)->Get_area() > object_in_process->Get_area())
			break;
	}
	objects_on_screen.insert(i, object_in_process);
}

void Paint::delete_object()
{
	for (auto i = objects_on_screen.begin(); i != objects_on_screen.end(); i++)
	{
		if ((*i)->Inside_my_rect(rect.left, rect.top))
		{
			delete (*i);
			i = objects_on_screen.erase(i);

			for (auto j = objects_on_screen.begin(); j != objects_on_screen.end();)
			{
				if (!(*j)->Valid())
				{
					delete (*j);
					j = objects_on_screen.erase(j);
				}
				else
					j++;
			}

			break;
		}
	}
}

bool Paint::is_object_picked()
{
	picked_object = NULL;
	for (auto i = objects_on_screen.begin(); i != objects_on_screen.end(); i++)
	{
		if ((*i)->Inside_my_rect(rect.left, rect.top))
		{
			picked_object = (*i);
			return true;
		}
	}
	return false;
}

void Paint::clear_object_list()
{
	for (auto i = objects_on_screen.begin(); i != objects_on_screen.end(); i++)
	{
		delete (*i);
	}
	objects_on_screen.clear();
}