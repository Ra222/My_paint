#pragma once
#include "Union.h"
#include "Rect.h"


class Box : public Union
{
public:
	Box();
	Box(RECT my_Rect, int my_ID);
	~Box();

	void Draw(HDC hDc);
	void Scale(int dx, int dy);

	void Grab();
	void Release();

	bool Write(std::fstream & f_object) const;
	bool Read(std::fstream & f_object);

private:
	void update_points();
};

