#include <string>
#include <cmath>

#include "gameManager.h"
#include "window.h"
#include "graphic.h"

const float GameManager::playerSpeed = 0.5f;
const float GameManager::rotateSpeed = 0.004f;
const float GameManager::jumpSpeed = 2.5f;

void GameManager::updatePlayer(Object* player, Object* playerFoot)
{
	setPlayerRotation(player);
	setPlayerVelocity(player, playerFoot);
}

void GameManager::setPlayerRotation(Object* player)
{
	Window& window = Window::getInstance();

	int mouseDeltaX, mouseDeltaY;
	window.getMousePosDelta(mouseDeltaX, mouseDeltaY);

	D3DXVECTOR3 angle = player->getAngle();
	angle.y -= mouseDeltaX * rotateSpeed;
	angle.z += mouseDeltaY * rotateSpeed;

	player->rotate(angle);
}

void GameManager::setPlayerVelocity(Object* player, Object* playerFoot)
{
	Window& window = Window::getInstance();

	int horizontalDir = window.isKeyPressed(KEY_A) - window.isKeyPressed(KEY_D);
	int verticalDir = window.isKeyPressed(KEY_W) - window.isKeyPressed(KEY_S);
	bool jump = window.isKeyPressed(SPACE);


	D3DXVECTOR3 velocity3 = D3DXVECTOR3(verticalDir, 0.0f, horizontalDir) * playerSpeed;
	
	if (isPlayerJumping)
	{
		player->applyGravity();
		velocity3.y = player->getVelocity().y;
	}
	else
	{
		player->cancelGravity();

		if (jump)
		{
			isPlayerJumping = true;
			velocity3.y = jumpSpeed;
			player->applyGravity();
		}
	}
	
	D3DXVECTOR4 velocity4 = D3DXVECTOR4(velocity3, 1.0f);
	D3DXMATRIX rotation;
	D3DXMatrixRotationY(&rotation, player->getAngleY());

	D3DXVec3Transform(&velocity4, &velocity3, &rotation);



	player->setVelocity(D3DXVECTOR3(velocity4));
}

void GameManager::checkPlayerJumping(ObjectIndex objectA, ObjectIndex objectB)
{
	if (objectA != PLAYER_FOOT && objectB != PLAYER_FOOT) return;
	if (false == isPlayerJumping) return;

	isPlayerJumping = false;
}

void GameManager::printFPS(unsigned long timeDelta)
{
	Window& window = Window::getInstance();

	int width = window.getWidth();

	RECT position = { 100, 0, width - 100, 100 };

	std::string fps = "FPS: " + std::to_string((1000 / timeDelta));

	font->DrawText(0, fps.c_str(), -1, &position, DT_TOP | DT_LEFT, Graphic::BLACK);

	isPlayerJumping = true;
}

void GameManager::printPlayerPosition(Object* player)
{
	Window& window = Window::getInstance();
	int width = window.getWidth();

	RECT position = { 100, 0, width - 100, 100 };

	D3DXVECTOR3 playerPosition = player->getPosition();

	std::string str = "X: " + std::to_string(isPlayerJumping) + "Y: " + std::to_string(playerPosition.y) + "Z: " + std::to_string(playerPosition.z);

	font->DrawText(0, str.c_str(), -1, &position, DT_TOP | DT_RIGHT, Graphic::BLACK);
}