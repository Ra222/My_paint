#pragma once
#include <cmath>
#include "Union.h"
#include "Line.h"


class Bond: public Union
{
public:
	Bond();
	Bond(int my_ID, int ID1, int ID2);
	~Bond();

	void Draw(HDC hDc);
	void Set_end_point(int ID2);

	bool Write(std::fstream & f_object) const;
	bool Read(std::fstream & f_object);

private:
	void update_points();
};
