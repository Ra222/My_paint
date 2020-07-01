#include "Trgl.h"



Trgl::Trgl()
{
	my_type = type_TRGL;
	hMy_Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	hMy_Brush = CreateSolidBrush(RGB(0, 0, 255));
}

Trgl::Trgl(RECT my_Rect, int my_ID) : Shape(my_Rect, my_ID)
{
	my_type = type_TRGL;
	hMy_Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	hMy_Brush = CreateSolidBrush(RGB(0, 0, 255));
}

Trgl::~Trgl()
{
}

void Trgl::Draw(HDC hDc)
{
	POINT temp[3] = {	{ my_Rect.left , my_Rect.bottom },
						{ (my_Rect.right - my_Rect.left)/2 + my_Rect.left,  my_Rect.top },
						{ my_Rect.right , my_Rect.bottom } };

	SelectObject(hDc, hMy_Pen);
	SelectObject(hDc, hMy_Brush);

	Polygon(hDc, temp, 3);
}

bool Trgl::Inside_my_rect(int x, int y) const
{
	POINT h_point = { (my_Rect.right - my_Rect.left) / 2 + my_Rect.left,  my_Rect.top };

	double A = Gauss_area(my_Rect.left, my_Rect.bottom, h_point.x, h_point.y, my_Rect.right, my_Rect.bottom);
	double A1 = Gauss_area(x, y, h_point.x, h_point.y, my_Rect.right, my_Rect.bottom);
	double A2 = Gauss_area(my_Rect.left, my_Rect.bottom, x, y, my_Rect.right, my_Rect.bottom);
	double A3 = Gauss_area(my_Rect.left, my_Rect.bottom, h_point.x, h_point.y, x, y);

	return (A == A1 + A2 + A3);
}

double Trgl::Gauss_area(int x1, int y1, int x2, int y2, int x3, int y3) const
{
	return abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2.0);
}