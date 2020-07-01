#pragma once
#include <cmath>
#include "ScreenObj.h"




class Shape: public ScreenObj
{
public:
	Shape();
	Shape(RECT my_Rect, int my_ID);
	virtual ~Shape();

	void Set_Style(HPEN hMy_Pen, HBRUSH hMy_Brush);

	const RECT& Get_rect() const;
	int Get_area() const;

	void Resize(int x, int y);
	void Scale(int dx, int dy);

	void ScaleUp(int c);
	void ScaleDown(int c);
	void ScaleRight(int c);
	void ScaleLeft(int c);

	bool Write(std::fstream & f_object) const;
	bool Read(std::fstream & f_object);

protected:
	void move(int dx, int dy);

	bool move_ID = true;
	RECT my_Rect = { 0 };

	HPEN hMy_Pen;
	HBRUSH hMy_Brush;
};