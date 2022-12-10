#pragma once
#include <unordered_map>

#include "enum.h"
#include "object.h"


class GameManager
{
private:
	ID3DXFont* font;
	unsigned long long score[10];

	bool isGameOver;

	unsigned long long elapsedTime;

	int myScore;

	void printFPS(unsigned long);
	void printElapsedTime();

	void printScoreBoard();
	void storeScore();

	std::string formatScore(unsigned long long);

public:
	GameManager() :
		isGameOver(false),
		score(),
		elapsedTime(0),
		font(NULL),
		myScore(0)
	{};
	~GameManager()
	{
		storeScore();
	}

	void init(ID3DXFont*);

	void gameOver();
	void printInfo(unsigned long);
};