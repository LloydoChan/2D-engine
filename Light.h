//Light.h
#pragma once

#include "Advanced2D.h"

namespace Advanced2D
{
	class Light
	{
		public:
			Light(int lightNum,D3DLIGHTTYPE type,D3DXVECTOR3 position,D3DXVECTOR3 direction,float range);
			~Light(){};
			float GetX()const {return p_light.Position.x;}
			float GetY()const {return p_light.Position.y;}
			float GetZ()const {return p_light.Position.z;}
			D3DLIGHTTYPE GetType()const {return p_type;}
			D3DCOLORVALUE GetColour()const {return p_light.Diffuse;}
			D3DXVECTOR3 GetPosition()const {return p_light.Position;}
			D3DXVECTOR3 GetDirection()const {return p_light.Direction;}
			void SetX(float value) {p_light.Position.x = value;}
			void SetY(float value) {p_light.Position.y = value;}
			void SetZ(float value) {p_light.Position.z = value;}
			void SetPosition(const D3DXVECTOR3& pos) {SetPosition(pos.x,pos.y,pos.z);}
			void SetPosition(float x,float y,float z) { p_light.Position.x = x; p_light.Position.y = y; p_light.Position.z = z;}
			void SetDirection(const D3DXVECTOR3& dir) {SetDirection(dir.x,dir.y,dir.z);}
			void SetDirection(float x,float y,float z) { p_light.Direction.x = x; p_light.Direction.y = y; p_light.Direction.z = z;}
			void Update();
			void Show();
			void Hide();
		private:
			D3DLIGHT9 p_light;
			D3DLIGHTTYPE p_type;
			int p_lightNum;
	};
};