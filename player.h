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

	bool isJumping;

public:
	Player() :
		playerSpeed(0.5f),
		rotateSpeed(0.004f),
		jumpSpeed(1.5f),
		isJumping(false)
	{

	}

	bool init(IDirect3DDevice9*);

	virtual void onBeforeUpdate();
	//virtual void onUpdate();
};

class PlayerFoot : public Cuboid
{
private: 
	bool isCollided;

public:
	PlayerFoot() :
		isCollided(false)
	{};

	bool init(IDirect3DDevice9*);

	virtual void onBeforeUpdate();
	virtual void onBeforeRender();
	virtual void onCollide();
};