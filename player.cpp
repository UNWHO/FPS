#include "player.h"
#include "window.h"
#include "scene.h"
#include "enum.h"
#include "graphic.h"

#include <iostream>

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

	setPosition({ 0.0f, 1.01f, 0.0f });

	setVelocity({ 0.0f, 0.0f, 0.0f });


	groundVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	applyGravity();
	return true;
}

void Player::onBeforeUpdate(unsigned long deltaTime)
{
	Window& window = Window::getInstance();


	// set rotation
	int mouseDeltaX, mouseDeltaY;
	window.getMousePosDelta(mouseDeltaX, mouseDeltaY);

	D3DXVECTOR3 angle = this->getAngle();
	angle.y -= mouseDeltaX * rotateSpeed * deltaTime;
	angle.z += mouseDeltaY * rotateSpeed * deltaTime;

	this->rotate(angle);

	if (window.isKeyPressed(KEY_R))
	{
		respawn();
		window.clearKeyStatus(KEY_R);
		return;
	}


	if (getPosition().y < -30.0f)
	{
		respawn();
	}



	// set velocity
	int horizontalDir = window.isKeyPressed(KEY_A) - window.isKeyPressed(KEY_D);
	int verticalDir = window.isKeyPressed(KEY_W) - window.isKeyPressed(KEY_S);
	

	D3DXVECTOR3 velocity3 = D3DXVECTOR3(verticalDir, 0.0f, horizontalDir);
	D3DXVec3Normalize(&velocity3, &velocity3);
	velocity3 *= window.isKeyPressed(SHIFT) ? playerRunSpeed : playerSpeed;


	// jump
	bool jump = window.isKeyPressed(SPACE);


	if (isJumping)
	{
		if (canDoubleJump && jump)
		{
			velocity3.y += jumpSpeed;
			canDoubleJump = false;
		}
		else
			velocity3.y = this->getVelocity().y;
	}
	else
	{
		velocity3.y = groundVelocity.y;
		if (jump)
		{
			isJumping = true;
			velocity3.y += jumpSpeed;
		}
	}

	if (window.isKeyPressed(RETURN))
	{
		cancelGravity();
		window.clearKeyStatus(RETURN);
	}
		
	if (window.isKeyPressed(KEY_C))
		applyGravity();

	//if (velocity3.y > jumpSpeed) velocity3.y = jumpSpeed;

	window.clearKeyStatus(SPACE);

	D3DXVECTOR4 velocity4 = D3DXVECTOR4(velocity3, 1.0f);
	D3DXMATRIX rotation;
	D3DXMatrixRotationY(&rotation, this->getAngleY());

	D3DXVec3Transform(&velocity4, &velocity3, &rotation);

	velocity4.x += groundVelocity.x;
	velocity4.z += groundVelocity.z;

	this->setVelocity(D3DXVECTOR3(velocity4));
}

void Player::onUpdate(unsigned long timeDelta)
{

}

void Player::respawn()
{
	if (previousSafeGround == NULL)
	{
		setPosition({ 0.0f, 1.01f, 0.0f });
		setVelocity({ 0.0f, 0.0f, 0.0f });
	}
	else
	{
		D3DXVECTOR3 position = previousSafeGround->getPosition();
		position.y += radius + 0.1f;
		setPosition(position);
		setVelocity({ 0.0f, 0.0f, 0.0f });
	}
}


bool PlayerFoot::init(IDirect3DDevice9* device, Player* player)
{
	if (NULL == device)
		return false;

	setMaterial(Graphic::CYAN, 5.0f);

	size.x = 0.19f;
	size.y = 0.01f;
	size.z = 0.19f;

	setDetectOnly();
	setShape(CUBOID);

	this->player = player;

	ID3DXMesh* cuboidMesh;
	if (FAILED(D3DXCreateBox(device, size.x, size.y, size.z, &cuboidMesh, NULL)))
		return false;
	setMesh(cuboidMesh);

	D3DXVECTOR3 position = player->getPosition();
	position.y -= (player->getRadius());

	this->setPosition(position);
	this->setVelocity({ 0.0f, 0.0f, 0.0f });
	this->setStatic();
	this->setInvisible();

	return true;
}

void PlayerFoot::attachToPlayer()
{
	D3DXVECTOR3 position = player->getPosition();
	position.y -= (player->getRadius() + size.y);

	this->setPosition(position);
}


void PlayerFoot::onBeforeUpdate(unsigned long deltaTime)
{
	if (false == isCollided)
	{
		player->isJumping = true;
	}

	isCollided = false;
	attachToPlayer();
}

void PlayerFoot::onBeforeRender()
{
	attachToPlayer();
}

void PlayerFoot::onCollide(Object* target)
{
	if (target->getShape() == SPHERE)
		return;

	D3DXVECTOR3 playerVelocity = player->getVelocity();
	D3DXVECTOR3 targetVelocity = target->getVelocity();

	if(D3DXVec3LengthSq(&targetVelocity) < 0.0001f)
		player->previousSafeGround = target;

	if (playerVelocity.y - targetVelocity.y > 0)
		return;

	isCollided = true;

 	player->isJumping = false;
	player->groundVelocity = targetVelocity;
}

