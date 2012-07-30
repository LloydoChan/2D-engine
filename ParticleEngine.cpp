//ParticleEngine.cpp

#include "ParticleEngine.h"

namespace Advanced2D
{
	ParticleEngine::ParticleEngine()
	{
		image = NULL;
		max = 100;
		length = 100;
		direction  = 0;
		alphaMin = 254;alphaMax = 255;
		minR = 0;maxR = 255;
		minG = 0;maxG = 255;
		minB = 0;maxB = 255;
		spread = 10;
		velocity = 1.0f;
		scale = 1.0f;
	}

	ParticleEngine::~ParticleEngine()
	{
		delete image;
		for(iter particle = particles.begin(); particle != particles.end(); particle++)
		{
			delete *particle;
		}
		particles.clear();
	}

	bool ParticleEngine::LoadImg(std::string imageFile)
	{
		image = new Texture;
		return image->Load(imageFile);
	}

	void ParticleEngine::Add()
	{
		static float PI_DIV_180 = 3.14159/180.0f;
		float vX,vY;
		Sprite* p = new Sprite;
		p->SetImage(image);
		p->SetPosition(position.GetX(),position.GetY());
		double variation = (rand() % spread - spread/2)/100.0f;

		double dir = direction - 90.0f;
		vX = cos(dir * PI_DIV_180) + variation;
		vY = sin(dir * PI_DIV_180) + variation;
		p->SetVelocity(vX * velocity,vY * velocity);

		int r = rand()%(maxR-minR)+minR;
		int g = rand()%(maxG-minG)+minG;
		int b = rand()%(maxB-minB)+minB;
		int a = rand()%(alphaMax-alphaMin)+alphaMin;
		p->SetColour(D3DCOLOR_RGBA(r,g,b,a));
	
		p->SetScale(scale);
		particles.push_back(p);
	}

	void ParticleEngine::Draw()
	{
		for(iter particle = particles.begin(); particle != particles.end(); particle++)
		{
			(*particle)->Draw();
		}
	}

	void ParticleEngine::Update()
	{
		static Timer timer;

		if((int)particles.size() < max)
		{
			if(timer.StopWatch(1))Add();
		}

		for(iter particle = particles.begin(); particle != particles.end(); particle++)
		{
			(*particle)->Move();

			if((*particle)->GetPosition().Distance2D(position)>length)
			{
				(*particle)->SetX(position.GetX());
				(*particle)->SetY(position.GetY());
			}
		}
	}


	void ParticleEngine::SetColourRange(int r1,int g1,int b1,int r2,int g2,int b2)
	{
		minR = r1;maxR = r2;
		minG = g1;maxG = g2;
		minB = b1;maxB = b2;
	}


};