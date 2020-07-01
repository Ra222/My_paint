#pragma once
#include <list>
#include "ScreenObj.h"
#include "Shape.h"


class Union : public ScreenObj
{
public:
	Union();
	Union(int my_ID);
	virtual ~Union();

	bool Valid() const;
	const RECT & Get_rect() const;
	int Get_area() const;
	void Resize(int x, int y);
	bool Inside_my_rect(int x, int y) const;

protected:
	void move(int dx, int dy);
	virtual void update_points() = 0;

	std::list<int> IDs;

	Shape* my_Avatar = NULL;
	bool move_ID = true;
};

