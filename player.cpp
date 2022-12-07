#include "player.h"
#include "window.h"
#include "scene.h"
#include "enum.h"
#include "graphic.h"

bool Player::init(IDirect3DDevice9* device)
{
	if (NULL == device)
		return false;

	radius = 0.1f;
	setShape(SPHERE);
	setMaterial(Graphic::WHITE, 5.0f);

	ID3DXMesh* sphereMesh;
	if (FAILED(D3DXCreateSphere(device, radius, 50, 50, &sphereMesh, NULL)))
		return false;
	setMesh(sphereMesh);

	setPosition({ -2.7f, radius, -0.9f });
	setVelocity({ 0.0f, 0.0f, 0.0f });
	applyGravity();

	return true;
}

void Player::onBeforeUpdate()
{
	Window& window = Window::getInstance();


	// set rotation
	int mouseDeltaX, mouseDeltaY;
	window.getMousePosDelta(mouseDeltaX, mouseDeltaY);

	D3DXVECTOR3 angle = this->getAngle();
	angle.y -= mouseDeltaX * rotateSpeed;
	angle.z += mouseDeltaY * rotateSpeed;

	this->rotate(angle);


	// set velocity
	int horizontalDir = window.isKeyPressed(KEY_A) - window.isKeyPressed(KEY_D);
	int verticalDir = window.isKeyPressed(KEY_W) - window.isKeyPressed(KEY_S);
	

	D3DXVECTOR3 velocity3 = D3DXVECTOR3(verticalDir, 0.0f, horizontalDir);
	D3DXVec3Normalize(&velocity3, &velocity3);
	velocity3 = velocity3 * playerSpeed;


	// jump
	bool jump = window.isKeyPressed(SPACE);


	if (isJumping)
	{
		velocity3.y = this->getVelocity().y;
	}
	else
	{
		if (jump)
		{
			isJumping = true;
			velocity3.y = jumpSpeed;
			applyGravity();
		}
	}


	D3DXVECTOR4 velocity4 = D3DXVECTOR4(velocity3, 1.0f);
	D3DXMATRIX rotation;
	D3DXMatrixRotationY(&rotation, this->getAngleY());

	D3DXVec3Transform(&velocity4, &velocity3, &rotation);

	this->setVelocity(D3DXVECTOR3(velocity4));
}


bool PlayerFoot::init(IDirect3DDevice9* device)
{
	if (NULL == device)
		return false;

	setMaterial(Graphic::CYAN, 5.0f);

	size.x = 0.2f;
	size.y = 0.005f;
	size.z = 0.2f;

	setDetectOnly();

	ID3DXMesh* cuboidMesh;
	if (FAILED(D3DXCreateBox(device, size.x, size.y, size.z, &cuboidMesh, NULL)))
		return false;
	setMesh(cuboidMesh);

	return true;
}


void PlayerFoot::onBeforeUpdate()
{
	if (false == isCollided)
	{
		Scene& scene = Scene::getInstance();
		Player* player = dynamic_cast<Player*>(scene.findObject(PLAYER));
		player->isJumping = true;
	}

	isCollided = false;
}

void PlayerFoot::onBeforeRender()
{
	Scene& scene = Scene::getInstance();
	Player* player = dynamic_cast<Player*>(scene.findObject(PLAYER));

	D3DXVECTOR3 position = player->getPosition();
	position.y -= player->getRadius();

	this->setPosition(position);
}

void PlayerFoot::onCollide()
{
	isCollided = true;

	Scene& scene = Scene::getInstance();
	Player* player = dynamic_cast<Player*>(scene.findObject(PLAYER));
	player->isJumping = false;
	player->cancelGravity();
	
}