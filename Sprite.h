//Sprite.h
#pragma once
#include "Vector3.h"
#include "Texture.h"
#include "Entity.h"
#include "Rect.h"


namespace Advanced2D
{

	enum CollisionType
	{
		COLLISION_NONE = 0,
		COLLISION_RECT = 1,
		COLLISION_DIST = 2,
		COLLISION_SPHERE = 3
	};

	class Sprite : public Entity
	{
		public:
			Sprite();
			virtual ~Sprite();
			bool LoadImg(std::string filename, D3DCOLOR transColour = D3DCOLOR_XRGB(255,0,255));
			void SetImage(Texture* img);
			void Move();
			void Animate();
			void Draw();

			void Transform();
			Vector3 GetPosition()const {return position;}
			float GetX()const {return position.GetX();}
			float GetY()const {return position.GetY();}
			Vector3 GetVelocity()const {return velocity;}
			int GetWidth() const {return width;}
			int GetHeight()const {return height;}
			bool IsVisible()const {return visible;}
			int GetState()const {return state;}
			int GetDirection()const {return direction;}
			int GetColumns()const {return animColumns;}
			D3DCOLOR GetColour()const{return colour;}
			int GetFrameTimer()const {return frameTimer;}
			int GetCurrentFrame()const {return curFrame;}
			int GetAnimationDirection()const {return animDir;}
			float GetRotation()const {return rotation;}
			float GetScale()const {return scaling;}
			int GetMoveTimer()const {return moveTimer;}
			bool IsCollidable()const {return collidable;}
			int GetXColOffset()const{return xColOffset;}
			int GetYColOffset()const{return yColOffset;}
			CollisionType GetCollisionMethod()const {return collisionMethod;}

			void SetPosition(const Vector3& pos){position = pos;}
			void SetPosition(float x,float y){position.SetX(x);position.SetY(y);}
			void  SetX(float value){position.SetX(value);}
			void  SetY(float value){position.SetY(value);}
			void  SetVelocity(const Vector3& vel) {velocity = vel;}
			void  SetVelocity(float x,float y) {velocity.SetX(x);velocity.SetY(y);}
			void  SetWidth(int value){width = value;}
			void  SetHeight(int value){height = value;}
			void  SetVisiblity(bool value) {visible = value;}
			void  SetState(int value) {state = value;}
			void  SetDirection(int value) {direction = value;}
			void  SetColumns(int value) {animColumns = value;}
			void  SetColour(D3DCOLOR col) {colour = col;}
			void  SetFrameTimer(int value){frameTimer = value;}
			void  SetCurrentFrame(int value){curFrame = value;}
			void  SetAnimationDirection(int value){animDir = value;}
			void  SetRotation(float value){rotation = value;}
			void  SetScale(float value){scaling = value;}
			void  SetTotalFrames(int value) {totalFrames = value;}
			void  SetMoveTimer(int value){moveTimer = value;}
			void  SetCollidability(bool value){collidable = value;}
			void  SetCollisionMethod(CollisionType val){collisionMethod = val;}
			void SetSize(int w,int h){width = w;height = h;}
			void SetXColOffset(int x) {xColOffset=x;}
			void SetYColOffset(int y) {yColOffset=y;}
		private:
			bool visible;
			bool alive;
			int lifeTimeLength;
			Timer lifeTimeTimer;
			int objectType;
			Vector3 position;
			Vector3 velocity;
			bool imageLoaded;
			int state;
			int direction;
		protected:
			Texture *image;
			int width,height;
			int xColOffset,yColOffset;
			int animColumns;
			int frameStart,frameTimer;
			int moveStart,moveTimer;
			bool collidable;
			enum CollisionType collisionMethod;
			int curFrame,totalFrames,animDir;
			float faceAngle,moveAngle;
			int animStartX,animStartY;
			float rotation,scaling;
			D3DXMATRIX matRotate;
			D3DXMATRIX matScale;
			D3DCOLOR colour;

	};
};