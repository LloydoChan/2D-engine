#include "Vector3.h"

namespace Advanced2D
{
	Vector3::Vector3()
	{
		elems[0] = elems[1] = elems[2] = 0;
	}

	Vector3::Vector3(const Vector3& v)
	{
		elems[0] = v[0];
		elems[1] = v[1];
		elems[2] = v[2];
	}

	Vector3::Vector3(float valueX,float valueY,float valueZ)
	{
		elems[0] = valueX;
		elems[1] = valueY;
		elems[2] = valueZ;
	}

	Vector3::Vector3(int valueX,int valueY,int valueZ)
	{
		elems[0] = (float)valueX;
		elems[1] = (float)valueY;
		elems[2] = (float)valueZ;
	}

	void Vector3::Set(const Vector3& v)
	{
		elems[0] = v[0];
		elems[1] = v[1];
		elems[2] = v[2];
	}

	void Vector3::Set(float valueX,float valueY,float valueZ)
	{
		elems[0] = valueX;
		elems[1] = valueY;
		elems[2] = valueZ;
	}

	void Vector3::Move(float valueX,float valueY,float valueZ)
	{
		elems[0] += valueX;
		elems[1] += valueY;
		elems[2] += valueZ;
	}

	const float& Vector3::operator[](int index) const
	{
		return elems[index];
	}

    float& Vector3::operator[](int index)
	{
		return elems[index];
	}

	Vector3& Vector3::operator*=(float val)
	{
		elems[0] *= val;
		elems[1] *= val;
		elems[2] *= val;
		return *this;
	}

	Vector3& Vector3::operator/=(float val)
	{
		elems[0] /= val;
		elems[1] /= val;
		elems[2] /= val;
		return *this;
	}

	Vector3& Vector3::operator+=(const Vector3& v)
	{
		elems[0] += v.GetX();
		elems[1] += v.GetY();
		elems[2] += v.GetZ();
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& v)
	{
		elems[0] -= v[0];
		elems[1] -= v[1];
		elems[2] -= v[2];
		return *this;
	}

	Vector3 Vector3::operator+(const Vector3& v)
	{
		float newX = elems[0] + v[0];
		float newY = elems[1] + v[1];
		float newZ = elems[2] + v[2];
		return Vector3(newX,newY,newZ);
	}

	Vector3 Vector3::operator-(const Vector3& v)
	{
		float newX = elems[0] - v[0];
		float newY = elems[1] - v[1];
		float newZ = elems[2] - v[2];
		return Vector3(newX,newY,newZ);
	}

	Vector3 Vector3::operator-()
	{
		float newX = -elems[0];
		float newY = -elems[1];
		float newZ = -elems[2];

		return Vector3(newX,newY,newZ);
	}

	Vector3 Vector3::operator/(float value)
	{
		float newX = elems[0] / value;
		float newY = elems[1] / value;
		float newZ = elems[2] / value;
		return Vector3(newX,newY,newZ);
	}

	Vector3 Vector3::operator*(float value)
	{
		float newX = elems[0] * value;
		float newY = elems[1] * value;
		float newZ = elems[2] * value;
		return Vector3(newX,newY,newZ);
	}

    Vector3 Vector3::operator*(float value)const
	{
		float newX = elems[0] * value;
		float newY = elems[1] * value;
		float newZ = elems[2] * value;
		return Vector3(newX,newY,newZ);
	}

	bool Vector3::operator==(const Vector3& v)
	{
		if(elems[0] != v[0]) return false;
		if(elems[1] != v[1]) return false;
		if(elems[2] != v[2]) return false;

		return true;
	}

	bool Vector3::operator!=(const Vector3& v)
	{
		if(elems[0] != v[0]) return true;
		if(elems[1] != v[1]) return true;
		if(elems[2] != v[2]) return true;

		return false;
	}

	Vector3& Vector3::operator=(const Vector3& v)
	{
		elems[0] = v[0];
		elems[1] = v[1];
		elems[2] = v[2];
		return *this;
	}

	float Vector3::Distance2D(const Vector3& v)
	{
		float xDist = abs(v[0] - elems[0]);
		float yDist = abs(v[1] - elems[1]);
		return sqrt(xDist*xDist + yDist*yDist);
	}

	float Vector3::Length()const
	{
		return sqrt(elems[0]*elems[0] + elems[1]*elems[1] + elems[2]*elems[2]);
	}

	float Vector3::DotProduct(const Vector3& v)
	{
		float xVal = elems[0] * v[0];
		float yVal = elems[1] * v[1];
		float zVal = elems[2] * v[2];
		return xVal + yVal + zVal;
	}

	Vector3 Vector3::CrossProduct(const Vector3& v)
	{
		float xVal = (elems[1] * v[2]) - (v[1] * elems[2]);
		float yVal = -((elems[0] * v[2]) - (v[0] * elems[2]));
		float zVal = (elems[0] * v[1]) - (v[0] * elems[1]);

		return Vector3(xVal,yVal,zVal);
	}

	Vector3 Vector3::Normalise()
	{
		float len = Length();
		float xVal = elems[0]/len;
		float yVal = elems[1]/len;
		float zVal = elems[2]/len;
		return Vector3(xVal,yVal,zVal);
	}

	Vector3 operator*(float val,Vector3& vec)
	{
		return vec * val;
	}

	Vector3 operator*(float val,const Vector3& vec)
	{
		return vec * val;
	}
};