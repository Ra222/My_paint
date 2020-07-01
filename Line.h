#pragma once
#include "Shape.h"


class Line : public Shape
{
public:
	Line();
	Line(RECT my_Rect, int my_ID);
	~Line();

	const RECT & Get_rect() const;
	int Get_area() const;

	void Draw(HDC hDc);
	bool Inside_my_rect(int x, int y) const;
	void Resize(int x, int y);

private:
	double d_min = 10;
};