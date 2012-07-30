//ParticleEngine.h
#pragma once
#include "Includes.h"
#include "Sprite.h"
#include "Vector3.h"

namespace Advanced2D
{
	class ParticleEngine 
	{
		public:
			ParticleEngine();
			virtual ~ParticleEngine();

			void SetPosition(const Vector3& pos) {position = pos;}
			void SetPosition(float x,float y,float z){position.SetX(x);position.SetY(y);position.SetZ(z);}
			void SetDirection(float dir){direction = dir;}
			void SetMax(int num){max = num;}
			void SetAlphaRange(int min,int max){alphaMin = min;alphaMax = max;}
			void SetColourRange(int r1,int g1,int b1,int r2,int g2, int b2);
			void SetSpread(int val){spread = val;}
			void SetLength(float len){length = len;}
			void SetVelocity(float vel){velocity = vel;}
			void SetScale(float scl){scale = scl;}
			void SetLifeTime(int lifeTime) {this->lifetime = lifeTime;}

			float GetDirection()const {return direction;}
			bool LoadImg(std::string imageFile);
			void Draw();
			void Update();
			void Add();
		private:
			std::vector<Sprite*> particles;
			typedef std::vector<Sprite*>::iterator iter;
			Texture* image;
			Vector3 position;
			float direction;
			float length;
			int max;
			int alphaMin,alphaMax;
			int minR,minG,minB,maxR,maxG,maxB;
			int spread;
			float velocity;
			float scale;
			int lifetime;
	};
};