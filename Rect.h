#pragma once
#include "Shape.h"


class Rect : public Shape
{
public:
	Rect();
	Rect(RECT my_Rect, int my_ID);
	~Rect();

	void Draw(HDC hDc);
	bool Inside_my_rect(int x, int y) const;
};