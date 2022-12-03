#pragma once
#include <unordered_map>

#include "enum.h"
#include "object.h"


class GameManager
{
private:
	static const float playerSpeed;
	static const float rotateSpeed;
	static const float jumpSpeed;

	bool isPlayerJumping;

	void setPlayerVelocity(Object*);
	void setPlayerRotation(Object*);

public:
	GameManager():
		isPlayerJumping(false)
	{}

	void updatePlayer(Object*);
	void checkPlayerJumping(Object*);
	


};