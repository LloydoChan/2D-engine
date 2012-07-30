//Entity.h

#pragma once
#include "Includes.h"
#include "Timer.h"

namespace Advanced2D
{
	enum RenderType
	{
		RENDER2D = 0,
		RENDER3D
	};

	class Entity
	{
		public:
			Entity(RenderType rendType);
			virtual ~Entity() {};
			virtual void Move() = 0;
			virtual void Animate() = 0;
			virtual void Draw() = 0;
			
			int GetID()const {return id;}
			RenderType GetRenderType()const {return renderType;}
			bool GetVisible()const{ return visible;}
			bool GetAlive()const {return alive;}
			const std::string& GetName()const {return name;}
			int GetLifeTime()const {return lifeTimeLength;}
			int GetObjectType(){return objectType;}
			
			void SetID(int value) {id = value;}
			void SetRenderType(RenderType type){renderType = type;}
			void SetName(std::string& nme){name = nme;}
			void SetVisible(bool value) {visible = value;}
			void SetAlive(bool value) {alive = value;}
			void SetLifeTime(int value){lifeTimeLength = value;lifeTimeTimer.Reset();}
			bool LifeTimeExpired() {return lifeTimeTimer.StopWatch(lifeTimeLength);}
			void SetObjectType(int value){objectType = value;}

		private:
			int id;
			std::string name;
			bool visible;
			bool alive;
			RenderType renderType;
			int objectType;
			int lifeTimeLength;
			Timer lifeTimeTimer;
			
	};
};