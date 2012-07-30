//rect.cpp
#include "Rect.h"

namespace Advanced2D
{
	Rect::Rect(int left,int top,int right,int bottom)
	{
		this->left = (float)left;
		this->top = (float)top;
		this->right = (float)right;
		this->bottom = (float)bottom;
	}

	Rect::Rect(float left,float top,float right,float bottom)
	{
		this->left   = left;
		this->top    = top;
		this->right  = right;
		this->bottom = bottom;
	}

	bool Rect::IsInside(const Vector3& point)
	{
		return IsInside(point.GetX(),point.GetY());
	}

	bool Rect::IsInside(float x,float y)
	{
		return (x > left && x < right && y < bottom && y > top);
	}

	bool Rect::IsInside(int x,int y)
	{
		return IsInside((float)x,float(y));
	}
};