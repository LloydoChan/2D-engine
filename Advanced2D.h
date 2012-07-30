//Advanced2D.h
#pragma once
#include <lua.hpp>
#include "Includes.h"
#include "Timer.h"
#include "Input.h"
#include "Audio.h"
#include "Entity.h"
#include "Sprite.h"
#include "Rect.h"
#include "Line.h"
#include "Light.h"
#include "ParticleEngine.h"
#include "Font.h"


#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define REVISION 0
#define START_BUTTON_VALUE 0x1000

//external variabled and functions
extern bool gameOver;
extern bool GamePreload();
extern bool GameInit(HWND);
extern void GameUpdate();
extern void GameEnd();
extern void GameRender3D();
extern void GameRender2D();
extern void GameKeyPress(int key);
extern void GameKeyRelease(int key);
extern void GameLeftThumbstickMove(SHORT stickValueX,SHORT stickValueY);
extern void GameRightThumbstickMove(SHORT stickValueX,SHORT stickValueY);
//extern void GameLeftTrigger(BYTE trigVal);
//extern void GameRightTrigger(BYTE trigVal);
extern void GamePadButtonPress(WORD buttons);
extern void GamePadButtonRelease(WORD buttons);
extern void GameMouseButton(int button);
extern void GameMouseMotion(int x,int y);
extern void GameMouseMove(int x,int y);
extern void GameMouseWheel(int wheel);
extern void GameEntityUpdate(Advanced2D::Entity* entity);
extern void GameEntityRender(Advanced2D::Entity* entity);
extern void GameEntityCollision(Advanced2D::Entity* entity1,Advanced2D::Entity* entity2);

namespace Advanced2D
{
	class Engine
	{
		public:
			Engine();
			virtual ~Engine();
			int Init(int width,int height,int colourDepth,bool fullScreen);
			void Close();
			void Update();
			void UpdateKeyboard();
			void UpdateMouse();
			void UpdateControllers();
			void Message(std::string message, std::string title = "ADVANCED 2D");
			void FatalError(std::string message, std::string title = "FATAL ERROR");
			void ShutDown();
			void ClearScene(D3DCOLOR colour);
			void SetIdentity();
			void SetDefaultMaterial();
			void SetAmbient(D3DCOLOR colourValue);
			int RenderStart();
			int RenderStop();
			int Render2DStart();
			int Render2DStop();
			int Release();

			//accessors/mutators
			bool IsPaused() {return p_pauseMode;}
			void SetPaused(bool value) {p_pauseMode = value;}
			LPDIRECT3DDEVICE9 GetDevice() const {return p_device;}
			LPDIRECT3DSURFACE9 GetBackBuffer() const {return p_backBuffer;}
			LPD3DXSPRITE GetSpriteHandler() const {return p_spriteHandler;}
			void SetWindowHandle(HWND hwnd) { p_windowHandle = hwnd;}
			HWND GetWindowHandle()const {return p_windowHandle;}
			std::string GetAppTitle()const {return p_appTitle;}
			void SetAppTitle(std::string value) {p_appTitle = value;}
			int GetVersionMajor()const {return p_versionMajor;}
			int GetVersionMinor()const  {return p_versionMinor;}
			int GetRevison() {return p_revision;}
			std::string GetVersionText()const;
			long GetFrameRateCore()const {return p_frameRateCore;}
			long GetFrameRateReal()const {return p_frameRateReal;}
			int GetScreenWidth()const {return p_screenWidth;}
			void SetScreenWidth(int value) {p_screenWidth = value;}
			int GetScreenHeight()const {return p_screenHeight;}
			void SetScreenHeight(int value){p_screenHeight = value;}
			int GetColourDepth()const {return p_colourDepth;}
			void SetColourDepth(int value) {p_colourDepth = value;}
			bool GetFullScreen()const{return p_fullScreen;}
			void SetFullScreen(bool value) {p_fullScreen = value;}
			bool GetMaximizeProcessor() {return p_maximizeProcessor;}
			void SetMaximizeProcessor(bool value) {p_maximizeProcessor = value;}
			int GetNumberControllers()const {return p_numControllers;}
			void SetNumberControllers(int num) {p_numControllers = num;}
			void AddEntity(Entity* entity);
			Entity* FindEntity(int objectType);
			Entity* FindEntity(std::string& name);
			//public audio handler
			Audio* p_audio;

			//collison handling
			bool Collision(Sprite* sp1,Sprite* sp2);
			bool CollisionBR(Sprite* sp1,Sprite* sp2);
			bool CollisionD(Sprite* sp1,Sprite* sp2);
			void TestForCollisions();
		private:
			int p_versionMajor, p_versionMinor, p_revision;
			HWND p_windowHandle;
			LPDIRECT3D9 p_d3d;
			LPDIRECT3DDEVICE9 p_device;
			LPDIRECT3DSURFACE9 p_backBuffer;
			LPD3DXSPRITE p_spriteHandler;
			Input* p_input;
			std::string p_appTitle;
			bool p_fullScreen;
			int p_screenWidth;
			int p_screenHeight;
			int p_colourDepth;
			int p_numControllers;
			bool p_pauseMode;
			D3DCOLOR p_ambientColour;
			bool p_maximizeProcessor;
			Timer p_coreTimer;
			long p_frameCountCore;
			long p_frameRateCore;
			Timer p_realTimer;
			long p_frameCountReal;
			long p_frameRateReal;
			Timer p_collisionTimer;
			Timer timedUpdate;
			std::list<Entity*> p_entities;

			void UpdateEntities();
			void Draw3DEntities();
			void Draw2DEntities();
			void BuryEntities();
	};
};

extern Advanced2D::Engine* g_engine;
