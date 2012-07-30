//Camera.h 

#pragma once 
#include "Advanced2D.h"

namespace Advanced2D
{
	class Camera
	{
		public:
			Camera();
			~Camera() {};

			void SetPerspective(float fov,float aspectRatio,float nearPlane,float farPlane);
			float GetNearPlane()const{return p_nearPlane;}
			void SetNearPlane(float value){p_nearPlane = value;}
			float GetFarPlane()const {return p_farPlane;}
			void SetFarPlane(float value) {p_farPlane = value;}
			float GetASpect()const {return p_aspect;}
			void SetAspect(float value) {p_aspect = value;}
			float GetFOV()const {return p_fov;}
			void SetFOV(float value) {p_fov = value;}
			void Update();

			D3DXVECTOR3 GetPosition()const {return p_posVector;}
			void SetPosition(float x,float y, float z)
				{p_posVector.x = x;p_posVector.y = y;p_posVector.z = z;}
			void SetPosition(const D3DXVECTOR3& pos) {p_posVector = pos;}
			float GetX()const {return p_posVector.x;}
			float GetY()const {return p_posVector.y;}
			float GetZ()const {return p_posVector.z;}
			void SetX(float value) {p_posVector.x = value;}
			void SetY(float value) {p_posVector.y = value;}
			void SetZ(float value) {p_posVector.z = value;}

			D3DXVECTOR3 GetTarget()const {return p_lookPointVector;}
			void SetTarget(const D3DXVECTOR3& value) {p_lookPointVector = value;}
			void SetTarget(float x,float y,float z) 
			{p_lookPointVector.x = x;p_lookPointVector.y = y;p_lookPointVector.z = z;}
		private:
			D3DXMATRIX p_projectionMatrix;
			D3DXMATRIX p_viewMatrix;
			D3DXVECTOR3 p_upVector;

			D3DXVECTOR3 p_posVector;
			D3DXVECTOR3 p_lookPointVector;
			float p_nearPlane;
			float p_farPlane;
			float p_fov;
			float p_aspect;

	};
};

