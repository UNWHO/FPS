#include "gameManager.h"
#include "window.h"

const float GameManager::playerSpeed = 0.5f;
const float GameManager::rotateSpeed = 0.004f;
const float GameManager::jumpSpeed = 1.0f;

void GameManager::updatePlayer(Object* player)
{
	setPlayerRotation(player);
	setPlayerVelocity(player);
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

void GameManager::setPlayerVelocity(Object* player)
{
	Window& window = Window::getInstance();

	int horizontalDir = window.isKeyPressed(KEY_A) - window.isKeyPressed(KEY_D);
	int verticalDir = window.isKeyPressed(KEY_W) - window.isKeyPressed(KEY_S);
	bool jump = window.isKeyPressed(SPACE);


	D3DXVECTOR3 velocity3 = D3DXVECTOR3(verticalDir, 0.0f, horizontalDir) * playerSpeed;
	
	if (isPlayerJumping) velocity3.y = player->getVelocity().y;
	else if (jump)
	{
		velocity3.y = jumpSpeed;
		isPlayerJumping = true;
	}
	
	D3DXVECTOR4 velocity4 = D3DXVECTOR4(velocity3, 1.0f);
	D3DXMATRIX rotation;
	D3DXMatrixRotationY(&rotation, player->getAngleY());

	D3DXVec3Transform(&velocity4, &velocity3, &rotation);


	player->setVelocity(D3DXVECTOR3(velocity4));
}

void GameManager::checkPlayerJumping(Object* player)
{
	D3DXVECTOR3 position = player->getPosition();
	if (position.y > 0.21f) return;

	position.y = 0.21f;
	player->setPosition(position);
	isPlayerJumping = false;
}