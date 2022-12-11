
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include <ctime>
#include "window.h"
#include "graphic.h"
#include "scene.h"


int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{

	srand(static_cast<unsigned int>(time(NULL)));

	Window& window = Window::getInstance();
	if (!window.init(hinstance))
		return 0;

	HWND hwnd = window.getHandle();
	Graphic& graphic = Graphic::getInstance();
	if (!graphic.init(hinstance, hwnd, true, D3DDEVTYPE_HAL))
		return 0;

	IDirect3DDevice9* device = graphic.getDevice();
	ID3DXFont* font = graphic.getFont();
	ID3DXFont* fontSmall = graphic.getFontSmall();

	Scene& scene = Scene::getInstance();
	if (!scene.init(device, font, fontSmall))
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}



	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	static unsigned long lastTime = timeGetTime();

	// main loop
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			unsigned long currTime = timeGetTime();
			if (currTime - lastTime < 1) continue;

			unsigned long timeDelta = currTime - lastTime;
			scene.update(); // manage keyboard input
			scene.render(timeDelta); // move objects and draw it

			lastTime = currTime;
		}
	}

	scene.destory();
	graphic.destory();
	window.destory();
	
	return 0;
}

