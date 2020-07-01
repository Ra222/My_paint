#pragma once
#include <windows.h>
#include <fstream>
#include <unordered_map>


enum type : unsigned short int { type_LINE, type_RECT, type_CRCL, type_TRGL, type_BOND, type_BOX };


class ScreenObj
{
public:
	ScreenObj();
	ScreenObj(int my_ID);
	virtual ~ScreenObj();

	virtual void Draw(HDC hDc) = 0;
	virtual bool Inside_my_rect(int x, int y) const = 0;

	virtual void Move(int dx, int dy);
	virtual void Resize(int x, int y) {};
	virtual void Scale(int dx, int dy) {};

	virtual const RECT& Get_rect() const = 0;
	virtual int Get_area() const = 0;

	virtual void Set_Style(HPEN hMy_Pen, HBRUSH hMy_Brush) {};

	virtual bool Write(std::fstream & f_object) const;
	virtual bool Read(std::fstream & f_object);

	virtual void Set_end_point(int ID2) {}
	virtual bool Valid() const { return true; }

	virtual void Grab() {}
	virtual void Release() {}

	type Get_type() const;
	int Get_ID() const;

protected:
	virtual void move(int dx, int dy) = 0;

	type my_type;
	int my_ID = 0;
	
	static bool current_move_ID;
	static std::unordered_map<int, ScreenObj*> objs;
};