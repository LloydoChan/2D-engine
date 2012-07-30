//Advanced2D.cpp
#include "Advanced2D.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <list>
#include "winMain.h"


namespace Advanced2D
{
	Engine::Engine()
	{
		srand(unsigned int(time(0)));
		p_maximizeProcessor = false;
		p_frameCountCore = 0;
		p_frameCountReal = 0;
		p_frameRateCore = 0;
		p_frameRateReal = 0;
		p_ambientColour = D3DCOLOR_RGBA(255,255,255,0);
		p_windowHandle = 0;
		p_pauseMode = false;
		p_versionMajor = VERSION_MAJOR;
		p_versionMinor = VERSION_MINOR;
		p_revision = REVISION;

		p_appTitle = "Advanced2D";
		p_screenWidth = 640;
		p_screenHeight = 480;
		p_colourDepth = 32;
		p_fullScreen = false;

		p_windowHandle = 0;
	}

	Engine::~Engine()
	{
		p_audio->StopAll();
		delete p_audio;
		delete p_input;
		if(p_device) p_device->Release();
		if(p_d3d) p_d3d->Release();
	}

	std::string Engine::GetVersionText()const
	{
		std::ostringstream s;
		s << "Advanced2D Engine v"<<p_versionMajor<<"."<<p_versionMinor<<"."<<p_revision;
		return s.str();
	}

	void Engine::Message(std::string message,std::string title)
	{
		MessageBox(0,message.c_str(),title.c_str(),0);
	}

	void Engine::FatalError(std::string message,std::string title)
	{
		Message(message,title);
		ShutDown();
	}

	int Engine::Init(int width,int height,int colourDepth,bool fullScreen)
	{
		p_screenHeight = height;
		p_screenWidth = width;
		p_fullScreen = fullScreen;
		p_colourDepth = colourDepth;

		p_d3d = Direct3DCreate9(D3D_SDK_VERSION);

		if(p_d3d == NULL)
			return 0;

		D3DDISPLAYMODE dm;
		p_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&dm);

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp,sizeof(d3dpp));
		d3dpp.Windowed = (!fullScreen);
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.BackBufferFormat = dm.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.BackBufferWidth = p_screenWidth;
		d3dpp.BackBufferHeight = p_screenHeight;
		d3dpp.hDeviceWindow = p_windowHandle;

		p_d3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			p_windowHandle,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&p_device);

		if(p_device == NULL) return 0;

		ClearScene(D3DCOLOR_XRGB(0,0,0));
		p_device->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&p_backBuffer);

		p_device->SetRenderState(D3DRS_ZENABLE,TRUE);
		p_device->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		p_device->SetRenderState(D3DRS_LIGHTING,TRUE);
		SetAmbient(p_ambientColour);

		HRESULT result = D3DXCreateSprite(p_device,&p_spriteHandler);
		if(result != D3D_OK) return 0;

		p_input = new Input(p_windowHandle);
		p_audio = new Audio;

		if(!p_audio->Init()) 
		{   Message("Error init audio");
			return 0;
		}

		if(!p_input->Init())
		{
			Message("Error init input");
			return 0;
		}

		if(!GameInit(p_windowHandle)) 
		{	
			Message("Error init game");
			return 0;
		}

		SetDefaultMaterial();

	

		return 1;

	}

	void Engine::SetIdentity()
	{
		D3DXMATRIX matrixWorld;
        D3DXMatrixIdentity(&matrixWorld);
        g_engine->GetDevice()->SetTransform(D3DTS_WORLD, &matrixWorld);
	}

	void Engine::SetDefaultMaterial()
	{
		D3DMATERIAL9 mat;
		ZeroMemory(&mat,sizeof(mat));
		mat.Diffuse.r = 1.0f;
		mat.Diffuse.g = 1.0f;
		mat.Diffuse.b = 1.0f;
		mat.Diffuse.a = 1.0f;
		p_device->SetMaterial(&mat);
	}

	void Engine::ClearScene(D3DCOLOR colour)
	{
		p_device->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,colour,1.0f,0);
	}

	void Engine::SetAmbient(D3DCOLOR colourValue)
	{
		p_ambientColour = colourValue;
		p_device->SetRenderState(D3DRS_AMBIENT,p_ambientColour);
	}

	int Engine::RenderStart()
	{
		if(!p_device)return 0;
		if(!p_device->BeginScene() != D3D_OK) return 0;
		return 1;
	}

	int Engine::RenderStop()
	{
		if(!p_device)return 0;
		if(p_device->EndScene()!=D3D_OK) return 0;
		if(p_device->Present(NULL,NULL,NULL,NULL) != D3D_OK) return 0;
		return 1;
	}

	int Engine::Render2DStart()
	{
		if(p_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND) != D3D_OK)
			return 0;
		else
			return 1;
	}

	int Engine::Render2DStop()
	{
		p_spriteHandler->End();
		return 1;
	}

	void Engine::ShutDown()
	{
		gameOver = true;
	}

	void Engine::Update()
	{
		//calculate framerate
		p_frameCountCore++;

		if(p_coreTimer.StopWatch(999))
		{
			p_frameRateCore = p_frameCountCore;
			p_frameCountCore = 0;
		}
		
		
			
		
		

		if(!p_pauseMode) UpdateEntities();

		//collison
		if(!p_pauseMode && p_collisionTimer.StopWatch(50))
		{
			TestForCollisions();
		}

		if(!timedUpdate.StopWatch(14))
		{
			if(!GetMaximizeProcessor())
			{
				Sleep(1);
			}
		}
		else
		{
			GameUpdate();
			p_frameCountReal++;
			if(p_realTimer.StopWatch(999))
			{
				p_frameRateReal = p_frameCountReal;
				p_frameCountReal = 0;
			}

			//update controller states and update the engine
			p_input->Update();
			UpdateKeyboard();
			UpdateMouse();
			UpdateControllers();
			//update the audio system
			p_audio->Update();

			//now start rendering
			RenderStart();
			GameRender3D();
			if(!p_pauseMode) Draw3DEntities();
			Render2DStart();
			if(!p_pauseMode) Draw2DEntities();
			GameRender2D();
			Render2DStop();
			RenderStop();

		
		}
		//garbage cleanup
		BuryEntities();
		
	}

	void Engine::UpdateKeyboard()
	{
		static char oldKeys[256];

		for(int key = 0; key < 255; key++)
		{
			if(p_input->GetKeyState(key) & 0x80)
			{
				GameKeyPress(key);
				oldKeys[key] = p_input->GetKeyState(key);
			}
			else if(oldKeys[key] & 0x80)
			{
				GameKeyRelease(key);
				oldKeys[key] = p_input->GetKeyState(key);
			}
		}
	}

	void Engine::UpdateMouse()
	{
		static int oldPosX = 0;
		static int oldPosY = 0;
		int deltaX = p_input->GetDeltaX();
		int deltaY = p_input->GetDeltaY();

		for(int button = 0; button < 3; button++)
		{
			if(p_input->GetMouseButton(button))
				GameMouseButton(button);

		}

		if(p_input->GetPosX() != oldPosX || p_input->GetPosY() != oldPosY)
		{
			GameMouseMove(p_input->GetPosX(),p_input->GetPosY());
			oldPosX = p_input->GetPosX();
			oldPosY = p_input->GetPosY();
		}

		if(deltaX != 0 ||deltaY)
		{
			GameMouseMotion(deltaX,deltaY);
		}

		int wheel = p_input->GetDeltaWheel();
		if(wheel != 0)
		{
			GameMouseWheel(wheel);
		}
	}

	void Engine::UpdateControllers()
	{
		static XINPUT_STATE oldStates[4];

		for(int controller = 0; controller < p_numControllers; controller++)
		{
			WORD buttons = p_input->GetButtons(controller);
			//use the fact that the values of the macros double to minimize code - e.g
			//XINPUT_GAMEPAD_A = 0x1000, XINPUT_GAMEPAD_B = 0x2000 etc
			//and use a similar strategy for the other buttons and thumbsticks
			for(int button = XINPUT_GAMEPAD_A; button <= XINPUT_GAMEPAD_Y; button *= 2)
			{
				if(buttons & button)
				{
					GamePadButtonPress(button);
					oldStates[controller].Gamepad.wButtons |= p_input->GetButtons(controller);
				}
				else if(oldStates[controller].Gamepad.wButtons & button)
				{
					GamePadButtonRelease(button);
					oldStates[controller].Gamepad.wButtons ^= button;
				}
			}//end face buttons buttons

			for(int button = XINPUT_GAMEPAD_START; button <= XINPUT_GAMEPAD_RIGHT_THUMB; button *= 2 )
			{
				if(buttons & button)
				{
					GamePadButtonPress(button);
					oldStates[controller].Gamepad.wButtons |= p_input->GetButtons(controller);
				}
				else if(oldStates[controller].Gamepad.wButtons & button)
				{
					GamePadButtonRelease(button);
					oldStates[controller].Gamepad.wButtons ^= button;
				}
			}//end 2nd set of face buttons

			for(int button = XINPUT_GAMEPAD_DPAD_UP; button <= XINPUT_GAMEPAD_DPAD_RIGHT; button *= 2 )
			{
				if(buttons & button)
				{
					GamePadButtonPress(button);
					oldStates[controller].Gamepad.wButtons |= p_input->GetButtons(controller);
				}
				else if(oldStates[controller].Gamepad.wButtons & button)
				{
					GamePadButtonRelease(button);
					oldStates[controller].Gamepad.wButtons ^= button;
				}
			}//end 3rd set of face buttons

			for(int button = XINPUT_GAMEPAD_LEFT_SHOULDER; button <= XINPUT_GAMEPAD_RIGHT_SHOULDER; button *= 2 )
			{
				if(buttons & button)
				{
					GamePadButtonPress(button);
					oldStates[controller].Gamepad.wButtons |= p_input->GetButtons(controller);
				}
				else if(oldStates[controller].Gamepad.wButtons & button)
				{
					GamePadButtonRelease(button);
					oldStates[controller].Gamepad.wButtons ^= button;
				}
			}//end 4th set of buttons

			
			BYTE stickValX = p_input->GetLeftStickX(controller);
			BYTE stickValY = p_input->GetLeftStickY(controller);

			GameLeftThumbstickMove(stickValX,stickValY);

			stickValX = p_input->GetRightStickX(controller);
			stickValY = p_input->GetRightStickY(controller);

			GameRightThumbstickMove(stickValX,stickValY);
		}//end controllers


	}

	void Engine::UpdateEntities()
	{
		std::list<Entity*>::iterator itr;
		Entity* entity;

		itr = p_entities.begin();

		while(itr != p_entities.end())
		{
			entity = *itr;

			if(entity->GetAlive())
			{
				entity->Move();
				entity->Animate();

				GameEntityUpdate(entity);

				if(entity->GetLifeTime() > 0)
				{
					if(entity->LifeTimeExpired())
					{
						entity->SetAlive(false);
					}
				}
			}

			++itr;
		}
	}



	void Engine::Draw2DEntities()
	{
		Entity* entity;
		std::list<Entity*>::iterator iter  = p_entities.begin();
		while(iter != p_entities.end())
		{
			entity = *iter;
			if(entity->GetRenderType() == RENDER2D)
			{
				if(entity->GetAlive() && entity->GetVisible())
				{
					entity->Draw();
					GameEntityRender(entity);
				}
			}
			++iter;
		}
	}

	void Engine::Draw3DEntities()
	{
		Entity* entity;
		std::list<Entity*>::iterator iter  = p_entities.begin();
		while(iter != p_entities.end())
		{
			entity = *iter;
			if(entity->GetRenderType() == RENDER3D)
			{
				if(entity->GetAlive() && entity->GetVisible())
				{
					entity->Draw();
					GameEntityRender(entity);
				}
			}
			iter++;
		}
	}

	void Engine::BuryEntities()
	{
		std::list<Entity*>::iterator itr = p_entities.begin();
		while(itr != p_entities.end())
		{
			if(!(*itr)->GetAlive())
			{
				delete (*itr);
				itr = p_entities.erase(itr);
			}

			else
				itr++;


		}
	}

	void Engine::AddEntity(Entity* entity)
	{
		static int id = 0;
		entity->SetID(id);
		p_entities.push_back(entity);
		id++;
	}

	Entity* Engine::FindEntity(int objectType)
	{
		std::list<Entity*>::iterator iter = p_entities.begin();

		while(iter != p_entities.end())
		{
			if((*iter)->GetAlive() && (*iter)->GetObjectType() == objectType)
			{
				return *iter;
			}
			else
				++iter;
		}
		return NULL;
	}

	Entity* Engine::FindEntity(std::string& name)
	{
		std::list<Entity*>::iterator iter = p_entities.begin();

		while(iter != p_entities.end())
		{
			if((*iter)->GetAlive() && (*iter)->GetName() == name)
			{
				return *iter;
			}
			else
				iter++;
		}
		return NULL;
	}

	void Engine::TestForCollisions()
	{
		std::list<Entity*>::iterator first;
		std::list<Entity*>::iterator second;

		Sprite* sprite1;
		Sprite* sprite2;

		first = p_entities.begin();
		while(first != p_entities.end())
		{
			if((*first)->GetRenderType() == RENDER2D)
			{
				sprite1 = (Sprite*)*first;

				if(sprite1->GetAlive() && sprite1->GetVisible() && sprite1->IsCollidable())
				{
					second = p_entities.begin();
					while(second != p_entities.end())
					{
						sprite2 = (Sprite*)*second;

						if(sprite2->GetAlive() && sprite2->GetVisible() && sprite2->IsCollidable() && sprite1 != sprite2)
						{
							if(Collision(sprite1,sprite2))
							{
								GameEntityCollision(sprite1,sprite2);
							}
						}

						second++;
					}//second loop
				}//first loop
				first++;
			}//render2D
		}//while
	}

	bool Engine::Collision(Sprite* sprite1,Sprite* sprite2)
	{
		switch(sprite1->GetCollisionMethod())
		{
			case COLLISION_RECT:
				return CollisionBR(sprite1,sprite2);
				break;
			case COLLISION_DIST:
				return CollisionD(sprite1,sprite2);
				break;
			case COLLISION_NONE:
			default:
				return false;
		}
	}

	bool Engine::CollisionBR(Sprite* sprite1,Sprite* sprite2)
	{
		bool rect = false;

		Rect* ra = new Rect(sprite1->GetX() + sprite1->GetXColOffset(),
			                sprite1->GetY() + sprite1->GetYColOffset(),
							sprite1->GetX() + sprite1->GetWidth() * sprite1->GetScale() - sprite1->GetXColOffset(),
							sprite1->GetY() + sprite1->GetHeight() * sprite1->GetScale() - sprite1->GetYColOffset());

		Rect* rb = new Rect(sprite2->GetX() + sprite2->GetXColOffset(),
			                sprite2->GetY() + sprite2->GetYColOffset(),
							sprite2->GetX() + sprite2->GetWidth() * sprite2->GetScale() - sprite2->GetXColOffset(),
							sprite2->GetY() + sprite2->GetHeight() * sprite2->GetScale() - sprite2->GetYColOffset());

		if(ra->IsInside(rb->GetLeft(),rb->GetTop())||
			ra->IsInside(rb->GetRight(),rb->GetTop())||
			ra->IsInside(rb->GetLeft(),rb->GetBottom())||
			ra->IsInside(rb->GetRight(),rb->GetBottom()))
				rect = true;

		delete ra;
		delete rb;
		return rect;
	}

	bool Engine::CollisionD(Sprite* sprite1,Sprite* sprite2)
	{
		float radius1,radius2;

		if(sprite1->GetWidth() > sprite1->GetHeight())
		{
			radius1 = ((sprite1->GetWidth() - sprite1->GetXColOffset()) * sprite1->GetScale())/2;
		}
		else
		{
			radius1 = ((sprite1->GetHeight() - sprite1->GetYColOffset()) * sprite1->GetScale())/2;
		}

		float x1 = sprite1->GetX() + radius1;
		float y1 = sprite1->GetY() + radius1;
		Vector3 vec1(x1,y1,0.0f);

		if(sprite2->GetWidth() > sprite2->GetHeight())
		{
			radius2 = ((sprite2->GetWidth()-sprite2->GetXColOffset()) * sprite2->GetScale())/2;
		}
		else
		{
			radius2 = ((sprite2->GetHeight()-sprite2->GetYColOffset()) * sprite2->GetScale())/2;
		}

		float x2 = sprite2->GetX() + radius2;
		float y2 = sprite2->GetY() + radius2;
		Vector3 vec2(x2,y2,0.0f);

		float dist = vec1.Distance2D(vec2);

		return (dist < radius1 + radius2);

	}

	void Engine::Close()
	{
		try
		{
			gameOver = true;
		}
		catch(...)
		{

		}

	}
};