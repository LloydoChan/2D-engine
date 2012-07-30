#include "Camera.h"

namespace Advanced2D
{
	Camera::Camera()
	{
		p_posVector = D3DXVECTOR3(0.0f,0.0f,10.0f);
		p_upVector = D3DXVECTOR3(0.0f,1.0f,0.0f);

		float ratio = 640/480;
		SetPerspective(3.14159f/4.0f,ratio,0.5f,2000.0f);
	}

	void Camera::SetPerspective(float fov,float ratio,float nearP,float farP)
	{
		p_fov = fov;
		p_aspect = ratio;
		p_nearPlane = nearP;
		p_farPlane = farP;
	}

	void Camera::Update()
	{
		D3DXMatrixLookAtLH(&p_viewMatrix,&p_posVector,&p_lookPointVector,&p_upVector);
		g_engine->GetDevice()->SetTransform(D3DTS_VIEW,&p_viewMatrix);

		D3DXMatrixPerspectiveFovLH(&p_projectionMatrix,p_fov,p_aspect,p_nearPlane,p_farPlane);
		g_engine->GetDevice()->SetTransform(D3DTS_PROJECTION,&p_projectionMatrix);
	}
};