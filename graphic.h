#pragma once
#include <d3dx9.h>

class Graphic
{
private:
	IDirect3DDevice9* device;
	ID3DXFont* font;

	Graphic() :
		device(NULL),
		font(NULL)
	{}
	Graphic(const Graphic& ref) {};
	Graphic& operator=(const Graphic& ref) {}
	~Graphic() {}

public:
	static Graphic& getInstance()
	{
		static Graphic Graphic;
		return Graphic;
	}

	bool init(HINSTANCE, HWND, bool, D3DDEVTYPE);
	void destory();

	IDirect3DDevice9* getDevice() const { return device; };
	ID3DXFont* getFont() const { return font; };


public:
	static const D3DXCOLOR WHITE;
	static const D3DXCOLOR BLACK;
	static const D3DXCOLOR RED;
	static const D3DXCOLOR GREEN;
	static const D3DXCOLOR BLUE;
	static const D3DXCOLOR YELLOW;
	static const D3DXCOLOR CYAN;
	static const D3DXCOLOR MAGENTA;
	static const D3DXCOLOR DARKRED;
	static const D3DXCOLOR BROWN;
};