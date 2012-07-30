//Rect.h
#pragma once
#include "Vector3.h"

namespace Advanced2D
{
	class Rect
	{
		public:
			Rect(int left,int top,int right, int bottom);
			Rect(float left,float top,float right, float bottom);
			virtual ~Rect(){};
			float GetLeft()const {return left;}
			float GetRight()const {return right;}
			float GetTop()const {return top;}
			float GetBottom()const {return bottom;}

			bool IsInside(const Vector3& point);
			bool IsInside(int x,int y);
			bool IsInside(float x,float y);
		private:
			float left,right,top,bottom;
	};
};