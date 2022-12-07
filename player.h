#pragma once
#include "sphere.h"
#include "cuboid.h"

class Player : public Sphere
{
	friend class PlayerFoot;

private:
	const float playerSpeed;
	const float rotateSpeed;
	const float jumpSpeed;




public:
	Player() :
		playerSpeed(0.5f),
		rotateSpeed(0.004f),
		jumpSpeed(1.0f),
		isJumping(false),
		canDoubleJump(false)
	{

	}	
	bool isJumping;
	bool canDoubleJump;
	bool init(IDirect3DDevice9*);

	virtual void onBeforeUpdate();
	virtual void onUpdate();
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

	virtual void onBeforeUpdate();
	virtual void onBeforeRender();
	virtual void onCollide(Object*);
};