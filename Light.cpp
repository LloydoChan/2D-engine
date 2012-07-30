#include "Light.h"

namespace Advanced2D
{
	Light::Light(int lightNum,D3DLIGHTTYPE type,D3DXVECTOR3 position,D3DXVECTOR3 direction,float range)
	{
		p_lightNum = lightNum;
		ZeroMemory(&p_light,sizeof(p_light));

		p_light.Diffuse.a = p_light.Diffuse.r = p_light.Diffuse.g = p_light.Diffuse.b = 1.0f;
		p_light.Ambient.a = p_light.Ambient.r = p_light.Ambient.g = p_light.Ambient.b = 1.0f;

		switch(type)
		{
			case D3DLIGHT_POINT:
				p_light.Type = D3DLIGHT_POINT;
				p_light.Position = position;
				p_light.Attenuation0 = 0.1f;
				p_light.Range = (float)range;
				break;
			case D3DLIGHT_SPOT:
				p_light.Type = D3DLIGHT_SPOT;
				p_light.Position = position;
				p_light.Direction = direction;
				p_light.Range = (float)range;
				p_light.Theta = 0.5f;
				p_light.Phi = 1.0f;
				p_light.Falloff = 1.0f;
				p_light.Attenuation0 = 1.0f;
				break;
			case D3DLIGHT_DIRECTIONAL:
			default:
				p_light.Type = D3DLIGHT_DIRECTIONAL;
				p_light.Range = (float)range;
				D3DXVec3Normalize((D3DXVECTOR3*)&p_light.Direction,&direction);

		}

		Show();
		Update();
		
	}

	void Light::Hide()
	{
		g_engine->GetDevice()->LightEnable(p_lightNum,false);
	}

	void Light::Show()
	{
		g_engine->GetDevice()->LightEnable(p_lightNum,true);
	}

	void Light::Update()
	{
		g_engine->GetDevice()->SetLight(p_lightNum,&p_light);
	}
};