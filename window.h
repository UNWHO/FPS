#pragma once
#include <Windows.h>
#include <windef.h>


enum KEY
{
	RETURN,
	SPACE,
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D
};

enum MOUSE
{
	LEFT,
	RIGHT
};

class Window
{
private:
	int width;
	int height;

	bool key[6];
	bool mouse[2];

	int mouse_x;
	int mouse_y;
	int mouse_dx;
	int mouse_dy;

	HWND hwnd;

	int centerX;
	int centerY;

	Window():
		key(),
		mouse(),
		mouse_x(0),
		mouse_y(0),
		mouse_dx(0),
		mouse_dy(0),
		width(0),
		height(0),
		hwnd(0),
		centerX(0),
		centerY(0)
	{};
	~Window() {};
	Window(const Window&) {};
	Window& operator=(const Window&) {};

public:
	static Window& getInstance()
	{
		static Window instance;
		return instance;
	}

	bool init(HINSTANCE);
	void destory();
	friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	HWND getHandle() const { return hwnd; };

	int getWidth() const { return width; };
	int getHeight() const { return height; };

	bool isKeyPressed(KEY key) { return this->key[key]; };
	bool isMouseClicked(MOUSE btn) { return mouse[btn]; };

	void getMousePos(int& x, int& y) { x = mouse_x; y = mouse_y; };
	void getMousePosDelta(int& dx, int& dy) { dx = mouse_dx; dy = mouse_dy; };
};