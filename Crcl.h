#pragma once
#include "Shape.h"


class Crcl : public Shape
{
public:
	Crcl();
	Crcl(RECT my_Rect, int my_ID);
	~Crcl();

	void Draw(HDC hDc);
	bool Inside_my_rect(int x, int y) const;
};

