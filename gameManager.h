#pragma once
#include <unordered_map>

#include "enum.h"
#include "object.h"
#include "scoreboard.h"

class GameManager
{
private:
	static const float playerSpeed;
	static const float rotateSpeed;
	static const float jumpSpeed;

	bool isPlayerJumping;

	void setPlayerVelocity(Object*, Object*);
	void setPlayerRotation(Object*);

	ID3DXFont* font;

public:
	GameManager() :
		isPlayerJumping(false)
	{};

	void init(ID3DXFont* font) { this->font = font; };

	void updatePlayer(Object*, Object*);
	void checkPlayerJumping(ObjectIndex, ObjectIndex);

	void printFPS(unsigned long);
	void printPlayerPosition(Object*);

	void printRanking(ID3DXFont*)const;

};