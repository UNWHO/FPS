#include <cstring>

#include "graphic.h"

const D3DXCOLOR Graphic::WHITE = D3DCOLOR_XRGB(255, 255, 255);
const D3DXCOLOR Graphic::BLACK = D3DCOLOR_XRGB(0, 0, 0);
const D3DXCOLOR Graphic::RED = D3DCOLOR_XRGB(255, 0, 0);
const D3DXCOLOR Graphic::GREEN = D3DCOLOR_XRGB(0, 255, 0);
const D3DXCOLOR Graphic::BLUE = D3DCOLOR_XRGB(0, 0, 255);
const D3DXCOLOR Graphic::YELLOW = D3DCOLOR_XRGB(255, 255, 0);
const D3DXCOLOR Graphic::CYAN = D3DCOLOR_XRGB(0, 255, 255);
const D3DXCOLOR Graphic::MAGENTA = D3DCOLOR_XRGB(255, 0, 255);
const D3DXCOLOR	Graphic::DARKRED = D3DCOLOR_XRGB(215, 0, 0);
const D3DXCOLOR	Graphic::BROWN = D3DCOLOR_XRGB(150, 75, 0);

bool Graphic::init(
	HINSTANCE hInstance,
	HWND hwnd,
	bool windowed,
	D3DDEVTYPE deviceType
)
{
	//
	// Init D3D: 
	//

	HRESULT hr = 0;

	// Step 1: Create the IDirect3D9 object.

	IDirect3D9* d3d9 = 0;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d9)
	{
		::MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}

	// Step 2: Check for hardware vp.

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// Step 3: Fill out the D3DPRESENT_PARAMETERS structure.

	RECT rc;
	GetClientRect(hwnd, &rc);
	UINT w = rc.right - rc.left;
	UINT h = rc.bottom - rc.top;
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = w;
	d3dpp.BackBufferHeight = h;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = windowed;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Step 4: Create the device.

	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		deviceType,         // device type
		hwnd,               // window associated with device
		vp,                 // vertex processing
		&d3dpp,             // present parameters
		&device);            // return created device

	if (FAILED(hr))
	{
		// try again using a 16-bit depth buffer
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			deviceType,
			hwnd,
			vp,
			&d3dpp,
			&device);

		if (FAILED(hr))
		{
			d3d9->Release(); // done with d3d9 object
			::MessageBox(0, "CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}

	d3d9->Release(); // done with d3d9 object


	// initialize font
	D3DXFONT_DESCA lf2;
	ZeroMemory(&lf2, sizeof(D3DXFONT_DESCA));
	lf2.Height = 85;
	lf2.Width = 35;
	lf2.Weight = 100;
	lf2.MipLevels = 0;
	lf2.Italic = false;
	lf2.CharSet = 0;
	lf2.OutputPrecision = 0;
	lf2.Quality = 0;
	lf2.PitchAndFamily = 0;
	std::strcpy(lf2.FaceName, "Arial"); // font style

	D3DXCreateFontIndirect(device, &lf2, &font);

	return true;
}

void Graphic::destory()
{
	device->Release();
	font->Release();
}