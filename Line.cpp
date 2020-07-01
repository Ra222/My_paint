#include "Line.h"

Line::Line()
{
	my_type = type_LINE;
	hMy_Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	hMy_Brush = CreateSolidBrush(RGB(255, 0, 0));
}

Line::Line(RECT my_Rect, int my_ID) : Shape(my_Rect, my_ID)
{
	my_type = type_LINE;
	hMy_Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	hMy_Brush = CreateSolidBrush(RGB(255, 0, 0));
}

Line::~Line()
{
}

const RECT& Line::Get_rect() const
{
	static RECT temp_Rect = { 0 };
	my_Rect.left < my_Rect.right ? (temp_Rect.left = my_Rect.left, temp_Rect.right = my_Rect.right) : (temp_Rect.left = my_Rect.right, temp_Rect.right = my_Rect.left);
	my_Rect.top < my_Rect.bottom ? (temp_Rect.top = my_Rect.top, temp_Rect.bottom = my_Rect.bottom) : (temp_Rect.top = my_Rect.bottom, temp_Rect.bottom = my_Rect.top);

	return temp_Rect;
}

int Line::Get_area() const
{
	return 0;
}

void Line::Draw(HDC hDc)
{
	SelectObject(hDc, hMy_Pen);
	SelectObject(hDc, hMy_Brush);

	MoveToEx(hDc, my_Rect.left, my_Rect.top, NULL);
	LineTo(hDc, my_Rect.right, my_Rect.bottom);
}

bool Line::Inside_my_rect(int x, int y) const
{
	RECT temp_Rect = { 0 };
	int a = 5;
	my_Rect.left < my_Rect.right ? (temp_Rect.left = my_Rect.left - a, temp_Rect.right = my_Rect.right + a) : (temp_Rect.left = my_Rect.right - a, temp_Rect.right = my_Rect.left + a);
	my_Rect.top < my_Rect.bottom ? (temp_Rect.top = my_Rect.top - a, temp_Rect.bottom = my_Rect.bottom + a) : (temp_Rect.top = my_Rect.bottom - a, temp_Rect.bottom = my_Rect.top + a);


	if ((temp_Rect.left <= x &&  x <= temp_Rect.right) &&
		(temp_Rect.top <= y &&  y <= temp_Rect.bottom))
	{
		double	a = (double)(my_Rect.top - my_Rect.bottom) / ((my_Rect.left - my_Rect.right) ? (my_Rect.left - my_Rect.right) : 1),
				b = -1,
				c = my_Rect.top - a*my_Rect.left,
				d = abs(a*x + b*y + c) / sqrt(a*a + b*b);

		return (d < d_min);
	}
	return false;
}

void Line::Resize(int x, int y)
{
	my_Rect.right = x;
	my_Rect.bottom = y;
}
