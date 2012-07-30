#include "Sprite.h"
#include "Advanced2D.h"

namespace Advanced2D
{
	Sprite::Sprite() : Entity(RENDER2D),image(NULL),imageLoaded(false),position(Vector3(0.0f,0.0f,0.0f)),velocity(Vector3(0.0f,0.0f,0.0f)),
						state(0),direction(0),width(1),height(1),curFrame(0),totalFrames(1),animDir(1),animColumns(1),
						frameStart(0),frameTimer(0),animStartX(0),animStartY(0),faceAngle(0.0f),moveAngle(0.0f),xColOffset(0),yColOffset(0),
						rotation(0.0f),scaling(1.0f),colour(0xFFFFFFFF),moveTimer(16),moveStart(0),collidable(true)
						
	{
		collisionMethod = COLLISION_RECT;
	}

	Sprite::~Sprite()
	{
		if(imageLoaded) delete image;
	}

	bool Sprite::LoadImg(std::string filename,D3DCOLOR transColour)
	{
		if(imageLoaded && image != NULL) delete image;

		image = new Texture;
		if(image->Load(filename,transColour))
		{
			SetSize(image->GetWidth(),image->GetHeight());
			imageLoaded = true;
			return true;
		}

		return false;
	}
	
	void Sprite::SetImage(Texture* img)
	{
		image = img;
		SetSize(img->GetWidth(),img->GetHeight());
		imageLoaded = false;
	}

	void Sprite::Transform()
	{
		D3DXMATRIX mat;
		D3DXVECTOR2 scale(scaling,scaling);
		D3DXVECTOR2 center((width*scaling)/2.0f,(height*scaling)/2.0f);
		D3DXVECTOR2 trans(GetX(),GetY());
		D3DXMatrixTransformation2D(&mat,NULL,0,&scale,&center,rotation,&trans);
		g_engine->GetSpriteHandler()->SetTransform(&mat);
	}

	void Sprite::Draw()
	{
		//calculate index values for sprite sheet
		int fX = (curFrame % animColumns) * width;
		int fY = (curFrame / animColumns) * height;
		RECT srcRect = {fX,fY,fX + width,fY + height};

		Transform();
		g_engine->GetSpriteHandler()->Draw(image->GetTexture(),&srcRect,NULL,NULL,colour);
	}

	void Sprite::Move()
	{
		if(moveTimer>0)
		{
			if(timeGetTime() > (DWORD)(moveStart + moveTimer))
			{
				moveStart = timeGetTime();
				SetX(GetX() + velocity.GetX());
				SetY(GetY() + velocity.GetY());
			}
		}
		else
		{
				SetX(GetX() + velocity.GetX());
				SetY(GetY() + velocity.GetY());
		}
	}

	void Sprite::Animate()
	{
		if(frameTimer > 0 )
		{
			if(timeGetTime() > (DWORD)(frameStart+frameTimer))
			{
				frameStart = timeGetTime();
				curFrame += animDir;

				if(curFrame < 0 ) curFrame = totalFrames - 1;

				if(curFrame > totalFrames - 1) curFrame = 0;
			}
		}
		else
		{
			curFrame += animDir;

			if(curFrame < 0 ) curFrame = totalFrames + 1;
			if(curFrame > totalFrames - 1) curFrame = 0;
		}
	}
};