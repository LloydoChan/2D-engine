#include "Maths.h"

namespace Advanced2D
{
	float Math::ToDegrees(float radian)
	{
		return radian * PI_UNDER_180;
	}

	float Math::ToRadians(float degrees)
	{
		return degrees * PI_OVER_180;
	}

	float Math::WrapAngleRadians(float radians)
	{
		float result = fmod(radians,PI*2.0f);
		if(result < 0.0f) result += 2.0f * PI;
		return result;
	}

	float Math::WrapAngleDegrees(float degrees)
	{
		float result = fmod(degrees,360.0f);
		if(result < 0.0f) result += 360.0f;
		return result;
	}

	float Math::LinearVelocityX(float angle)
	{
		angle -= 90.0f;
		if(angle < 0) angle += 360.0f;
		return cos(angle * PI_OVER_180);
	}

	float Math::LinearVelocityY(float angle)
	{
		angle -= 90.0f;
		if(angle < 0) angle += 360.0f;
		return sin(angle * PI_OVER_180);
	}

	Vector3 Math::LinearVelocity(float angle)
	{
		float fX = LinearVelocityX(angle);
		float fY = LinearVelocityY(angle);
		return Vector3(fX,fY,0.0f);
	}

	float Math::AngleToTarget(float x1,float y1,float x2,float y2)
	{
		float deltaX = x2-x1;
		float deltaY = y2-y1;
		return atan2(deltaX,deltaY);
	}

	float Math::AngleToTarget(const Vector3& vec1,const Vector3& vec2)
	{
		return AngleToTarget(vec1.GetX(),vec1.GetY(),vec2.GetX(),vec2.GetY());
	}

	float Math::Distance(float x1,float y1,float x2,float y2)
	{
		float deltaX = x2-x1;
		float deltaY = y2-y1;
		return sqrt((deltaX*deltaX)+(deltaY*deltaY));
	}

	float Math::Distance(const Vector3& vec1,const Vector3& vec2)
	{
		return Distance(vec1.GetX(),vec1.GetY(),vec2.GetX(),vec2.GetY());
	}

	float Math::Length(float x1,float y1,float z1)
	{
		return sqrt(x1*x1 + y1*y1 + z1*z1);
	}

	float Math::Length(const Vector3& vec)
	{
		return Length(vec.GetX(),vec.GetY(),vec.GetZ());
	}

	float Math::DotProduct(float x1,float y1,float z1,float x2,float y2,float z2)
	{
		return (x1*x2 + y1*y2 + z1*z2);
	}

	float Math::DotProduct(const Vector3& vec1,const Vector3& vec2)
	{
		return DotProduct(vec1.GetX(),vec1.GetY(),vec1.GetZ(),vec2.GetX(),vec2.GetY(),vec2.GetZ());
	}

	Vector3 Math::CrossProduct(float x1,float y1,float z1,float x2,float y2,float z2)
	{
		float xVal = y1 * z2 - y2 * z1;
		float yVal = -(x1 * z2 - x2 * z1);
		float zVal = x1 * y2 - x2 * y1;

		return Vector3(xVal,yVal,zVal);
	}

	Vector3 Math::CrossProduct(const Vector3& vec1,const Vector3& vec2)
	{
		return CrossProduct(vec1.GetX(),vec1.GetY(),vec1.GetZ(),vec2.GetX(),vec2.GetY(),vec2.GetZ());
	}

	Vector3 Math::Normal(float x,float y,float z)
	{
		float length = Length(x,y,z);
		if(length != 0 ) length = 1/length;
		float nx = length * x;
		float ny = length * y;
		float nz = length * z;
		return Vector3(nx,ny,nz);
	}

	Vector3 Math::Normal(const Vector3& vec)
	{
		return Normal(vec.GetX(),vec.GetY(),vec.GetZ());
	}

};