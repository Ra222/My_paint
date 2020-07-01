#include "Rect.h"



Rect::Rect()
{
	my_type = type_RECT;
	hMy_Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	hMy_Brush = CreateSolidBrush(RGB(0, 255, 0));
}

Rect::Rect(RECT my_Rect, int my_ID): Shape(my_Rect, my_ID)
{
	my_type = type_RECT;
	hMy_Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	hMy_Brush = CreateSolidBrush(RGB(0, 255, 0));
}

Rect::~Rect()
{
}

void Rect::Draw(HDC hDc)
{
	SelectObject(hDc, hMy_Pen);
	SelectObject(hDc, hMy_Brush);

	Rectangle(hDc, my_Rect.left, my_Rect.top, my_Rect.right, my_Rect.bottom);
}

bool Rect::Inside_my_rect(int x, int y) const
{
	return PtInRect(&my_Rect, POINT{ x, y });
}