#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Scoreboard
{
private:
	std::fstream file;
public:
	void manageFile(std::fstream, std::pair<std::string, float>const&);
	bool compareNameTime(std::pair<std::string, float>const&, std::pair<std::string, float>const&);
};
