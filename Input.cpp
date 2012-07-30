//Input.cpp
#include "Input.h"

namespace Advanced2D
{
	Input::Input(HWND wndw) : window(wndw),numControllers(0)
	{
		ZeroMemory(keyState,256);
		ZeroMemory(&mouseState,sizeof(mouseState));
		ZeroMemory(&state,sizeof(XINPUT_STATE)*4);

		di= NULL;
		keyboard = NULL;
		mouse = NULL;

	}

	Input::~Input()
	{
		XInputEnable(false);
		di->Release();
		keyboard->Release();
		mouse->Release();
	}

	bool Input::Init()
	{
		DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&di,NULL);

		di->CreateDevice(GUID_SysKeyboard,&keyboard,NULL);
		keyboard->SetDataFormat(&c_dfDIKeyboard);
		keyboard->SetCooperativeLevel(window,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		keyboard->Acquire();

		di->CreateDevice(GUID_SysMouse,&mouse,NULL);
		mouse->SetDataFormat(&c_dfDIMouse);
		mouse->SetCooperativeLevel(window,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		mouse->Acquire();

		XInputEnable(true);
		return true;
	}

	void Input::Update()
	{
		keyboard->Poll();
		if(!SUCCEEDED(keyboard->GetDeviceState(sizeof(keyState),(LPVOID)&keyState)))
		{
			keyboard->Acquire();
		}

		mouse->Poll();
		if(!SUCCEEDED(mouse->GetDeviceState(sizeof(mouseState),(LPVOID)&mouseState)))
		{
			mouse->Acquire();
		}

		for(DWORD controller = 0; controller < numControllers; controller++)
		{
			XInputGetState(controller,&state[controller]);
		}

		GetCursorPos(&position);
		ScreenToClient(window,&position);
	}

	bool Input::GetMouseButton(char button)
	{
		return (mouseState.rgbButtons[button] & 0x80);
	}
	
	WORD Input::GetButtons(int controller)
	{
		return state[controller].Gamepad.wButtons;
	}

	BYTE Input::GetLeftTrigger(int controller)
	{
		return state[controller].Gamepad.bLeftTrigger;
	}

	BYTE Input::GetRightTrigger(int controller)
	{
		return state[controller].Gamepad.bRightTrigger;
	}

	SHORT Input::GetLeftStickX(int controller)
	{
		return state[controller].Gamepad.sThumbLX;
	}

	SHORT Input::GetLeftStickY(int controller)
	{
		return state[controller].Gamepad.sThumbLY;
	}

	SHORT Input::GetRightStickX(int controller)
	{
		return state[controller].Gamepad.sThumbRX;
	}

	SHORT Input::GetRightStickY(int controller)
	{
		return state[controller].Gamepad.sThumbRY;
	}
};