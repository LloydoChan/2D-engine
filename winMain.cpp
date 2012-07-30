//winMain.cpp
#include <sstream>
#include "winMain.h"
#include "Advanced2D.h"

#define KEY_DOWN(vk) ((GetAsyncKeyState(vk)& 0x8000)?1:0)

HINSTANCE g_hInstance;
HWND g_hWnd;
int g_nCmdShow;

Advanced2D::Engine *g_engine;

bool gameOver;

LRESULT WINAPI WinProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_QUIT:
		case WM_CLOSE:
		case WM_DESTROY:
			gameOver = true;
			break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg;
	srand(time(0));
	g_hInstance = hInstance;
	g_nCmdShow = nCmdShow;
	DWORD dwStyle,dwExStyle;
	RECT windowRect;

	g_engine = new Advanced2D::Engine();

	if(!GamePreload())
	{
		MessageBox(g_hWnd,"Error in preload!","Error",MB_OK);
		return 0;
	}

	char title[255];
	sprintf(title,"%s",g_engine->GetAppTitle().c_str());

	windowRect.left = (long)0;
	windowRect.right = (long)g_engine->GetScreenWidth();
	windowRect.top = (long)0;
	windowRect.bottom = (long)g_engine->GetScreenHeight();

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = title;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	if(g_engine->GetFullScreen())
	{
		DEVMODE dm;
		memset(&dm,0,sizeof(dm));
		dm.dmSize = sizeof(dm);
		dm.dmPelsWidth = g_engine->GetScreenWidth();
		dm.dmPelsHeight = g_engine->GetScreenHeight();
		dm.dmBitsPerPel = g_engine->GetColourDepth();
		dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if(ChangeDisplaySettings(&dm,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			MessageBox(NULL,"Display Mode Failed",NULL,MB_OK);
			g_engine->SetFullScreen(false);
		}

		dwStyle = WS_POPUP;
		dwExStyle = WS_EX_APPWINDOW;
		ShowCursor(FALSE);
	}
	else
	{
		dwStyle = WS_OVERLAPPEDWINDOW;
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	}

	AdjustWindowRectEx(&windowRect,dwStyle,FALSE,dwExStyle);

	g_hWnd = CreateWindowEx(
		0,
		title,
		title,
		dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		0,0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		0,
		0,
		g_hInstance,
		0);

	if(!g_hWnd)
	{
		MessageBox(g_hWnd,"Error creating prog window!","Error",MB_OK);
		return 0;
	}

	ShowWindow(g_hWnd,g_nCmdShow);
	UpdateWindow(g_hWnd);

	g_engine->SetWindowHandle(g_hWnd);
	if(!g_engine->Init(g_engine->GetScreenWidth(),g_engine->GetScreenHeight(),
		g_engine->GetColourDepth(),g_engine->GetFullScreen()))
	{
		MessageBox(g_hWnd,"Error init engine","Error",MB_OK);
		return 0;
	}

	gameOver = false;
	while(!gameOver)
	{
		while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		g_engine->Update();
	}

	if(g_engine->GetFullScreen())
	{
		ShowCursor(TRUE);
	}

	GameEnd();
	delete g_engine;

	return 1;
}