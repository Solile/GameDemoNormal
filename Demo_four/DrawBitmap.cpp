#include <windows.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
using namespace std;
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
// program settings
const string APPTITLE = "Draw Bitmap Program";
// macro to detect key presses
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
// Srceen resolution
const int SCREENW = 1024;
const int SCREENH = 768;
// Direct3D objects
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backbuffer = NULL;
LPDIRECT3DSURFACE9 surface = NULL;
bool gameover = false;

// Game initialization function
bool Game_Init(HWND hwnd)
{
	// Initialize Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d)
	{
		MessageBox(hwnd, "Error initializing Direct3D", "Error", MB_OK);
		return FALSE;
	}
	// set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREENW;
	d3dpp.BackBufferHeight = SCREENH;
	d3dpp.hDeviceWindow = hwnd;
	// create Direct3D device
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
	if (!d3ddev)
	{
		MessageBox(hwnd, "Error creating Direct3D device", "Error", MB_OK);
		return FALSE;
	}
	// clear the backbuffer to black
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	// create surface
	HRESULT result = d3ddev->CreateOffscreenPlainSurface(
		SCREENW, SCREENH,	// width & height of the surface
		D3DFMT_X8R8G8B8,	//surface format
		D3DPOOL_DEFAULT,	//memory pool to use
		&surface,			//pointer ro the surface
		NULL);				//reserved (always NULL)

	if (result != D3D_OK) return false;
	result = D3DXLoadSurfaceFromFile(surface, NULL, NULL, "photo.jpg",
		NULL, D3DX_DEFAULT, 0, NULL);
	if (result != D3D_OK) return false;
	return true;

}
// Game Update function
void Game_Run(HWND hwnd)
{
	if (!d3ddev) return;
	// create pointer to the back buffer
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	// start rendering
	if (d3ddev->BeginScene())
	{
		// draw the surface to the backbuffer
		d3ddev->StretchRect(surface, NULL, backbuffer, NULL, D3DTEXF_NONE);
		// stop rendering
		d3ddev->EndScene();
		// copy the back buffer to the screen
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}
	// check for esape key (to exit program)
	if (KEY_DOWN(VK_SPACE))
		PostMessage(hwnd, WM_DESTROY, 0, 0);
}
// Game Shutdown function
void Game_End(HWND hwnd)
{
	if (surface)
	{
		surface->Release();
		surface = NULL;
	}
	if (d3ddev)
	{
		d3ddev->Release();
		d3ddev = NULL;
	}
	if (d3d)
	{
		d3d->Release();
		d3d = NULL;
	}
}

// The window event callback function 
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		gameover = true;
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// Main Windows entry function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// create the window
	MSG msg;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.lpszMenuName = NULL;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	wc.lpszClassName = "MainWindowClass";
	if (!RegisterClassEx(&wc))
		return FALSE;

	//create a new window
	HWND window = CreateWindow("MainWindowClass", APPTITLE.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, SCREENW, SCREENH,
		NULL, NULL, hInstance, NULL);

	if (window == 0) return 0;
	ShowWindow(window, nCmdShow);
	UpdateWindow(window);
	if (!Game_Init(window)) return 0;

	while (!gameover)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Game_Run(window);
	}
	//Game_End(window);
	return msg.wParam;
}