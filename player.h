#pragma once
#include "sphere.h"
#include "cuboid.h"

class Player : public Sphere
{
	friend class PlayerFoot;

private:
	const float playerSpeed;
	const float playerRunSpeed;
	const float rotateSpeed;
	const float jumpSpeed;

	D3DXVECTOR3 groundVelocity;

	Object* previousSafeGround;

	void respawn();

public:
	Player() :
		playerSpeed(0.5f),
		playerRunSpeed(1.75f),
		rotateSpeed(0.00025f),
		jumpSpeed(1.0f),
		isJumping(true),
		canDoubleJump(false),
		previousSafeGround(NULL)
	{

	}	
	bool isJumping;
	bool canDoubleJump;
	bool init(IDirect3DDevice9*);

	virtual void onBeforeUpdate(unsigned long);
	virtual void onUpdate(unsigned long);
	void getDoubleJumpItem() { canDoubleJump = true; };
};

class PlayerFoot : public Cuboid
{
private: 
	bool isCollided;
	Player* player;

public:
	PlayerFoot() :
		isCollided(false)
	{};

	bool init(IDirect3DDevice9*, Player* player);
	void attachToPlayer();

	virtual void onBeforeUpdate(unsigned long);
	virtual void onBeforeRender();
	virtual void onCollide(Object*);
};