#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>

#include "gameManager.h"
#include "window.h"
#include "graphic.h"
#include "scene.h"
#include "player.h"
#include "file.h"

void GameManager::init(ID3DXFont* font, ID3DXFont* fontSmall)
{
	 this->font = font;
	 this->fontSmall = fontSmall;

	 std::vector<std::string> savedScores = File::read("score.txt");
	 if (savedScores.size() != 10)
	 {
		 for (int i = 0; i < 10; i++)
			 score[i] = -1;
		 return;
	 }

	 for (int i = 0; i < 10; i++)
	 {
		 score[i] = std::atoi(savedScores[i].c_str());
	 }
}

void GameManager::storeScore()
{
	std::vector<std::string> scoreStr;
	for (int i = 0; i < 10; i++)
	{
		scoreStr.push_back(score[i] != -1 ? std::to_string(score[i]) : "-1");
	}

	File::write("score.txt", scoreStr);
}

void GameManager::printInfo(unsigned long timeDelta)
{
	if (isGameOver)
	{
		printScoreBoard();
	}
	else
	{
		printFPS(timeDelta);
		printElapsedTime();
	}
}

void GameManager::gameOver()
{
	this->isGameOver = true;
	
	int i;
	for (i = 0; i < 10; i++)
	{
		if (score[i] == -1 || elapsedTime < score[i])
			break;
	}

	if (i == 10) return;

	for (int j = 9; j > i; j--)
	{
		score[j] = score[j - 1];
	}
	score[i] = elapsedTime;

	myScore = score[i];
}

void GameManager::printFPS(unsigned long timeDelta)
{
	Window& window = Window::getInstance();

	int width = window.getWidth();

	RECT position = { 100, 0, width - 100, 100 };

	std::string fps = "FPS: " + std::to_string((1000 / timeDelta));

	font->DrawText(0, fps.c_str(), -1, &position, DT_TOP | DT_LEFT, Graphic::BLACK);

	elapsedTime += timeDelta;
}

void GameManager::printElapsedTime()
{
	Window& window = Window::getInstance();
	int width = window.getWidth();

	RECT position = { 100, 0, width - 100, 100 };

	std::string str = "Score : " + formatScore(elapsedTime);
	font->DrawText(0, str.c_str(), -1, &position, DT_TOP | DT_RIGHT, Graphic::BLACK);
}

void GameManager::printScoreBoard()
{
	Window& window = Window::getInstance();
	int width = window.getWidth();
	int height = window.getHeight();

	RECT position = { 100, 100, width - 100, height - 100 };

	std::string str = "Congratulation!\n";
	font->DrawText(0, str.c_str(), -1, &position, DT_TOP | DT_CENTER, Graphic::WHITE);

	

	str = "";
	for (int i = 0; i < 10; i++)
	{
		str += std::to_string(i + 1) + " : ";
		if (score[i] != (unsigned long long)(-1)) str += formatScore(score[i]);
		else str += "00:00:000";

		str += '\n';
	}
	fontSmall->DrawText(0, str.c_str(), -1, &position, DT_VCENTER | DT_CENTER, Graphic::BLACK);

	str = "My Score : " + formatScore(myScore);

	font->DrawText(0, str.c_str(), -1, &position, DT_BOTTOM | DT_CENTER, Graphic::WHITE);
}

std::string GameManager::formatScore(unsigned long long score)
{
	std::ostringstream ss;

	ss << std::setw(2) << std::setfill('0') << std::to_string(score / 60000) << ":";
	score %= 60000;

	ss << std::setw(2) << std::setfill('0') << std::to_string(score / 1000) << ":";
	score %= 1000;

	ss << std::setw(3) << std::setfill('0') << std::to_string(score);
	
	return ss.str();
}