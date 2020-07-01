#include "Bond.h"




Bond::Bond()
{
	my_type = type_BOND;
	my_Avatar = new Line;
	my_Avatar->Set_Style(CreatePen(PS_SOLID, 3, RGB(0, 0, 0)), CreateSolidBrush(RGB(0, 125, 0)));
}

Bond::Bond(int my_ID, int ID1, int ID2) : Union(my_ID)
{
	my_type = type_BOND;
	my_Avatar = new Line;
	my_Avatar->Set_Style(CreatePen(PS_SOLID, 3, RGB(0, 0, 0)), CreateSolidBrush(RGB(0, 125, 0)));
	IDs.push_back(ID1);
	IDs.push_back(ID2);
}

Bond::~Bond()
{
}

void Bond::Set_end_point(int ID2)
{
	IDs.back() = ID2;
	update_points();
}

void Bond::Draw(HDC hDc)
{
	update_points();
	my_Avatar->Draw(hDc);
}

bool Bond::Write(std::fstream & f_object) const
{
	if (!ScreenObj::Write(f_object))
	{
		return false;
	}

	int temp = IDs.front();
	if (!f_object.write((char*)&temp, sizeof(int)))
	{
		return false;
	}

	temp = IDs.back();
	if (!f_object.write((char*)&temp, sizeof(int)))
	{
		return false;
	}

	return true;
}

bool Bond::Read(std::fstream & f_object)
{
	if (!ScreenObj::Read(f_object))
	{
		return false;
	}

	int temp = 0;
	if (!f_object.read((char*)&temp, sizeof(int)))
	{
		return false;
	}
	IDs.push_back(temp);
	if (!f_object.read((char*)&temp, sizeof(int)))
	{
		return false;
	}
	IDs.push_back(temp);

	return true;
}

void Bond::update_points()
{
	try
	{
		RECT temp_point = objs.at(IDs.front())->Get_rect();
		my_Avatar->ScaleLeft((temp_point.right + temp_point.left) / 2);
		my_Avatar->ScaleUp((temp_point.bottom + temp_point.top) / 2);

		temp_point = objs.at(IDs.back())->Get_rect();
		my_Avatar->ScaleRight((temp_point.right + temp_point.left) / 2);
		my_Avatar->ScaleDown((temp_point.bottom + temp_point.top) / 2);
	}
	catch (std::out_of_range)
	{}
}