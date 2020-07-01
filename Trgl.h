#pragma once
#include "Shape.h"
#include <cmath>


class Trgl : public Shape
{
public:
	Trgl();
	Trgl(RECT my_Rect, int my_ID);
	~Trgl();

	void Draw(HDC hDc);
	bool Inside_my_rect(int x, int y) const;

private:
	double Gauss_area(int x1, int y1, int x2, int y2, int x3, int y3) const;
};

