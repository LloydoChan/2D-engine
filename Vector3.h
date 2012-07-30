//Vector3.h
#pragma once
#include "Includes.h"

namespace Advanced2D
{
	class Vector3
	{
		public:
			Vector3();
			Vector3(const Vector3& v);
			Vector3(float valueX,float valueY,float valueZ);
			Vector3(int valueX,int valueY,int valueZ);
			void Set(float valueX,float valueY,float valueZ);
			void Set(const Vector3& v);
			void SetX(float value) {elems[0] = value;}
			void SetY(float value) {elems[1] = value;}
			void SetZ(float value) {elems[2] = value;}

			float GetX()const {return elems[0];}
			float GetY()const {return elems[1];}
			float GetZ()const {return elems[2];}

			void Move(float xValue,float yValue,float zValue);

			//compound operators
			Vector3& operator+=(const Vector3& v);
			Vector3& operator-=(const Vector3& v);
			Vector3& operator*=(float val);
			Vector3& operator/=(float val);

			//access array operators
			const float& operator[](int index) const;
			float& operator[](int index);

			//arithmetic operators
			Vector3 operator+(const Vector3& v);
			Vector3 operator-(const Vector3& v);
			Vector3 operator-();
			Vector3 operator*(float val);
			Vector3 operator*(float val)const;
			Vector3 operator/(float val);

			//boolean operators
			bool operator==(const Vector3& v);
			bool operator!=(const Vector3& v);

			//assignment
			Vector3& operator=(const Vector3& v);

			//other operators
			float Distance2D(const Vector3& v);
			float Length()const;
			float DotProduct(const Vector3& v);
			Vector3 CrossProduct(const Vector3& v);
			Vector3 Normalise();
		private:
			float elems[3];
	};

	Vector3 operator*(float val,Vector3& vec);
	Vector3 operator*(float val,const Vector3& vec);
};