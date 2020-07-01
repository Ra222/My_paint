#include "Crcl.h"



Crcl::Crcl()
{
	my_type = type_CRCL;
	hMy_Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	hMy_Brush = CreateSolidBrush(RGB(255, 0, 0));
}

Crcl::Crcl(RECT my_Rect, int my_ID) : Shape(my_Rect, my_ID)
{
	my_type = type_CRCL;
	hMy_Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	hMy_Brush = CreateSolidBrush(RGB(255, 0, 0));
}

Crcl::~Crcl()
{
}

void Crcl::Draw(HDC hDc)
{
	SelectObject(hDc, hMy_Pen);
	SelectObject(hDc, hMy_Brush);

	Ellipse(hDc, my_Rect.left, my_Rect.top, my_Rect.right, my_Rect.bottom);
}

bool Crcl::Inside_my_rect(int x, int y) const
{
	POINT center = {	(my_Rect.right - my_Rect.left) / 2 + my_Rect.left,
						(my_Rect.bottom - my_Rect.top) / 2 + my_Rect.top	};

	int p = (pow((x - center.x), 2) / pow(center.x - my_Rect.left, 2)) +
			(pow((y - center.y), 2) / pow(center.y - my_Rect.top, 2));

	return !p;
}