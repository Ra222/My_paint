#include "Box.h"



Box::Box()
{
	my_type = type_BOX;
	my_Avatar = new Rect;
	my_Avatar->Set_Style(CreatePen(PS_SOLID, 1, RGB(0, 0, 0)), CreateSolidBrush(RGB(90, 255, 170)));
}

Box::Box(RECT my_Rect, int my_ID) : Union(my_ID)
{
	my_type = type_BOX;
	my_Avatar = new Rect(my_Rect, my_ID+1);
	my_Avatar->Set_Style(CreatePen(PS_SOLID, 1, RGB(0, 0, 0)), CreateSolidBrush(RGB(90, 255, 170)));
}

Box::~Box()
{
}

void Box::Draw(HDC hDc)
{
	my_Avatar->Draw(hDc);
}

void Box::Scale(int dx, int dy)
{
	my_Avatar->Scale(dx, dy);
}

void Box::Grab()
{
	update_points();
}

void Box::Release()
{
	IDs.clear();
}

bool Box::Write(std::fstream & f_object) const
{
	if (!ScreenObj::Write(f_object))
	{
		return false;
	}

	return my_Avatar->Write(f_object);
}

bool Box::Read(std::fstream & f_object)
{
	if (!ScreenObj::Read(f_object))
	{
		return false;
	}

	type temp;
	if (!f_object.read((char*)&temp, sizeof(temp)))
	{
		return false;
	}
	return my_Avatar->Read(f_object);
}

void Box::update_points()
{
	RECT temp_rect = { 0 };
	IDs.clear();
	try
	{
		for (auto i = objs.begin(); i != objs.end(); i++)
		{
			temp_rect = (*i).second->Get_rect();
			if (my_Avatar->Inside_my_rect(temp_rect.left, temp_rect.top) && my_Avatar->Inside_my_rect(temp_rect.right, temp_rect.bottom))
				IDs.push_back((*i).first);
		}
	}
	catch (std::out_of_range)
	{}
}
