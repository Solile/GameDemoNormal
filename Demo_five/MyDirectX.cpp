#include "MyDirectX.h"
#include <iostream>
using namespace std;
// Direct3D variables
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backbuffer = NULL;
// DirectInput variables
LPDIRECTINPUT8 dinput = NULL;
LPDIRECTINPUTDEVICE8 dimouse = NULL;
LPDIRECTINPUTDEVICE8 dikeyboard = NULL;
DIMOUSESTATE mouse_state;
char keys[256];
XINPUT_GAMEPAD controllers[4];
// Direct3D initialization
bool Direct3D_Init(HWND hwnd, int width, int height, bool fullscreen)
{
	// Initialize Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d) return false;
	// set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.hDeviceWindow = hwnd;
	// create Direct3D device
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
	if (!d3ddev) return false;
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	return true;
}
void Direct3D_Shutdown()
{
	if (d3ddev) d3ddev->Release();
	if (d3d) d3d->Release();
}
void DrawSurface(LPDIRECT3DSURFACE9 dest, float x, float y, LPDIRECT3DSURFACE9 source)
{
	// get width/height from source surface
	D3DSURFACE_DESC desc;
	source->GetDesc(&desc);
	// create tects for drawing
	RECT source_rect = { 0,0,(long)desc.Width,(long)desc.Height };
	RECT dest_rect = { (long)x,(long)y,(long)x + desc.Width,(long)y + desc.Height };
	// draw the source surfacen onto the dest
	d3ddev->StretchRect(source, &source_rect, dest, &dest_rect, D3DTEXF_NONE);
}
LPDIRECT3DSURFACE9 LoadSurface(string filename)
{
	LPDIRECT3DSURFACE9 image = 0;

	// get width/height from bitmap file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
	if (result != D3D_OK) return NULL;
	// create surface
	result = d3ddev->CreateOffscreenPlainSurface(
		info.Width, info.Height, D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT, &image, NULL);
	if (result != D3D_OK) return NULL;
	// load surface from file into newly created surface
	result = D3DXLoadSurfaceFromFile(image, NULL, NULL,
		filename.c_str(), NULL, D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0), NULL);
	// make sure file was loaded okay
	if (result != D3D_OK) return NULL;
	return image;
}
// DirectInput initialization
bool DirectInput_Init(HWND hwnd)
{
	// initialize DirectInput object
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, NULL);
	// initialize the keyboard
	dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);
	dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	dikeyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	dikeyboard->Acquire();
	// initialize the mouse
	dinput->CreateDevice(GUID_SysMouse, &dimouse, NULL);
	dimouse->SetDataFormat(&c_dfDIMouse);
	dimouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	dimouse->Acquire();
	d3ddev->ShowCursor(false);
	return true;
}
void DirectInput_Update()
{
	// update mouse
	dimouse->GetDeviceState(sizeof(mouse_state), (LPVOID)&mouse_state);
	// update keyboard
	dikeyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
	// update controllers
	for (int i = 0; i < 4; i++)
	{
		ZeroMemory(&controllers[i], sizeof(XINPUT_STATE));
		XINPUT_STATE state;
		DWORD result = XInputGetState(i, &state);
		if (result == 0)controllers[0] = state.Gamepad;
	}
}
void DirectInput_Shutdown()
{
	if (dikeyboard)
	{
		dikeyboard->Unacquire();
		dikeyboard->Release();
		dikeyboard = NULL;
	}
	if (dimouse)
	{
		dimouse->Unacquire();
		dimouse->Release();
		dimouse = NULL;
	}
}
// return key press state
int Key_Down(int key)
{
	return(keys[key] & 0x80);
}
// return mouse button state
int Mouse_Button(int button)
{
	return mouse_state.rgbButtons[button] & 0x80;
}
// return mouse x movevent
int Mouse_X()
{
	return mouse_state.lX;
}
// return mouse y movevent
int Mouse_Y()
{
	return mouse_state.lY;
}
// Vibrate the controller
void XInput_Vibrate(int contNum, int amount)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = amount;
	vibration.wRightMotorSpeed = amount;
	XInputSetState(contNum, &vibration);
}
// return true if controller is plugged in
bool XInput_Controller_Found()
{
	XINPUT_CAPABILITIES caps;
	ZeroMemory(&caps, sizeof(XINPUT_CAPABILITIES));
	XInputGetCapabilities(0, XINPUT_FLAG_GAMEPAD, &caps);
	if (caps.Type != 0) return false;
	return true;
}

