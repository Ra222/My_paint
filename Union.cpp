#include "Union.h"



Union::Union()
{
}

Union::Union(int my_ID) : ScreenObj(my_ID)
{
}

Union::~Union()
{
	if (my_Avatar)
		delete my_Avatar;
}

bool Union::Valid() const
{
	try
	{
		for (auto i = IDs.begin(); i != IDs.end(); i++)
		{
			if (!objs.at(*i)->Valid())
				return false;
		}
	}
	catch (std::out_of_range)
	{
		return false;
	}
	return true;
}

const RECT& Union::Get_rect() const
{
	return my_Avatar->Get_rect();
}

int Union::Get_area() const
{
	return (my_Avatar->Get_area() * 1000);
}

void Union::Resize(int x, int y)
{
	my_Avatar->Resize(x, y);
}

bool Union::Inside_my_rect(int x, int y) const
{
	return my_Avatar->Inside_my_rect(x, y);
}

void Union::move(int dx, int dy)
{
	if (this->move_ID == current_move_ID)
		return;
	this->move_ID = current_move_ID;

	try
	{
		for (auto i = IDs.begin(); i != IDs.end(); i++)
			objs.at(*i)->Move(dx, dy);
	}
	catch (std::out_of_range)
	{
		return;
	}

	my_Avatar->Move(dx, dy);
}
