//maths.h - 
#pragma once
#include "Includes.h"
#include "Vector3.h"

namespace Advanced2D
{
	const float PI = 3.14159f;
	const float PI_OVER_180 = PI/ 180.0f;
	const float PI_UNDER_180 = 180.0f/PI;

	class Math
	{
	public:
		static float ToDegrees(float radian);
		static float ToRadians(float degrees);
		static float WrapAngleDegrees(float degrees);
		static float WrapAngleRadians(float radians);
		static float LinearVelocityX(float angle);
		static float LinearVelocityY(float angle);
		static Vector3 LinearVelocity(float angle);
		static float AngleToTarget(float x1,float y1,float x2,float y2);
		static float AngleToTarget(const Vector3& pt1,const Vector3& pt2);
		static float Distance(float x1,float y1,float x2,float y2);
		static float Distance(const Vector3& pt1,const Vector3& pt2);
		static float Length(const Vector3& vec);
		static float Length(float x,float y,float z);
		static float DotProduct(const Vector3& vec1,const Vector3& vec2);
		static float DotProduct(float x1,float y1,float z1,float x2,float y2,float z2);
		static Vector3 CrossProduct(const Vector3& vec1,const Vector3& vec2);
		static Vector3 CrossProduct(float x1,float y1,float z1,float x2,float y2,float z2);
		static Vector3 Normal(float x,float y,float z);
		static Vector3 Normal(const Vector3& vec);
		
	};
};