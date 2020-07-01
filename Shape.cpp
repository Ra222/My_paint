#include "Shape.h"



Shape::Shape()
{
}

Shape::Shape(RECT my_Rect, int my_ID) : ScreenObj(my_ID)
{
	this->my_Rect = my_Rect;
}

Shape::~Shape()
{
}

void Shape::Set_Style(HPEN hMy_Pen, HBRUSH hMy_Brush)
{
	this->hMy_Pen = hMy_Pen;
	this->hMy_Brush = hMy_Brush;
}

const RECT& Shape::Get_rect() const
{
	return my_Rect;
}

int Shape::Get_area() const
{
	return (my_Rect.right - my_Rect.left)*(my_Rect.bottom - my_Rect.top);
}

void Shape::Resize(int x, int y)
{
	if ( x - my_Rect.left < my_Rect.right - x )
		my_Rect.left = x;
	else
		my_Rect.right = x;

	if ( y - my_Rect.top < my_Rect.bottom - y )
		my_Rect.top = y;
	else
		my_Rect.bottom = y;
}

void Shape::Scale(int dx, int dy)
{
	InflateRect(&my_Rect, dx, dy);
}

void Shape::ScaleUp(int c)
{
	my_Rect.top = c;
}

void Shape::ScaleDown(int c)
{
	my_Rect.bottom = c;
}

void Shape::ScaleRight(int c)
{
	my_Rect.right = c;
}

void Shape::ScaleLeft(int c)
{
	my_Rect.left = c;
}

bool Shape::Write(std::fstream& f_object) const
{
	if (!ScreenObj::Write(f_object))
	{
		return false;
	}

	if (!f_object.write((char*)&my_Rect, sizeof(my_Rect)))
	{
		return false;
	}

	return true;
}

bool Shape::Read(std::fstream & f_object)
{
	if (!ScreenObj::Read(f_object))
	{
		return false;
	}

	if (!f_object.read((char*)&my_Rect, sizeof(my_Rect)))
	{
		return false;
	}

	return true;
}

void Shape::move(int dx, int dy)
{
	if (this->move_ID == current_move_ID)
		return;
	OffsetRect(&my_Rect, dx, dy);
	this->move_ID = current_move_ID;
}
