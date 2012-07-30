//Line.h
#pragma once
#include "Vector3.h"
#include "Entity.h"


namespace Advanced2D
{
	class Line: public Entity
	{
		public:
			Line();
			virtual ~Line();
			bool Init();
			void Move();
			void Animate();
			void Draw();

			D3DXVECTOR2 GetStartPoint()const{return points[0];}
			D3DXVECTOR2 GetEndPoint()const{return points[1];}
			D3DCOLOR GetColor()const{return color;}

			void SetStartPoint(const Vector3& start){this->points[0] = D3DXVECTOR2(start.GetX(),start.GetY());}
			void SetEndPoint(const Vector3& end){this->points[1] = D3DXVECTOR2(end.GetX(),end.GetY());}
			void SetColor(D3DCOLOR& color){this->color = color;}
		private:
			D3DXVECTOR2 points[2];
			D3DCOLOR color;
			LPD3DXLINE line;
			int width;
	};
}