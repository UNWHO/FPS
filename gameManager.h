#pragma once
#include <unordered_map>

#include "enum.h"
#include "object.h"


class GameManager
{
private:
	ID3DXFont* font;

public:
	void init(ID3DXFont* font) { this->font = font; };

	void printFPS(unsigned long);
	void printPlayerPosition(Object*);
};