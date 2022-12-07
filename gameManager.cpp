#include <string>
#include <cmath>

#include "gameManager.h"
#include "window.h"
#include "graphic.h"

void GameManager::printFPS(unsigned long timeDelta)
{
	Window& window = Window::getInstance();

	int width = window.getWidth();

	RECT position = { 100, 0, width - 100, 100 };

	std::string fps = "FPS: " + std::to_string((1000 / timeDelta));

	font->DrawText(0, fps.c_str(), -1, &position, DT_TOP | DT_LEFT, Graphic::BLACK);

	//isPlayerJumping = true;
}

void GameManager::printPlayerPosition(Object* player)
{
	Window& window = Window::getInstance();
	int width = window.getWidth();

	RECT position = { 100, 0, width - 100, 100 };

	D3DXVECTOR3 playerPosition = player->getPosition();

	std::string str = "X: " + std::to_string(playerPosition.x) + "Y: " + std::to_string(playerPosition.y) + "Z: " + std::to_string(playerPosition.z);

	font->DrawText(0, str.c_str(), -1, &position, DT_TOP | DT_RIGHT, Graphic::BLACK);
}