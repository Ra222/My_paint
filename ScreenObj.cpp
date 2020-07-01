#include "ScreenObj.h"

bool ScreenObj::current_move_ID = true;
std::unordered_map<int, ScreenObj*> ScreenObj::objs = std::unordered_map<int, ScreenObj*>();

ScreenObj::ScreenObj()
{
}

ScreenObj::ScreenObj(int my_ID) : my_ID(my_ID)
{
	objs[my_ID] = this;
}

ScreenObj::~ScreenObj()
{
	objs.erase(my_ID);
}

void ScreenObj::Move(int dx, int dy)
{
	static bool move_flag = false;

	if (!move_flag)
	{
		move_flag = true;
		current_move_ID = !current_move_ID;

		move(dx, dy);

		move_flag = false;
	}
	else
	{
		move(dx, dy);
	}
}

bool ScreenObj::Write(std::fstream & f_object) const
{
	if(	!f_object.write((char*)&my_type,	sizeof(my_type)) ||
		!f_object.write((char*)&my_ID,		sizeof(my_ID))	)
	{
		return false;
	}
	return true;
}

bool ScreenObj::Read(std::fstream & f_object)
{
	if (!f_object.read((char*)&my_ID, sizeof(my_ID)))
	{
		return false;
	}
	objs[my_ID] = this;

	return true;
}

type ScreenObj::Get_type() const
{
	return my_type;
}

int ScreenObj::Get_ID() const
{
	return my_ID;
}
