#pragma once
#include <fstream>
#include <iostream>
#include <string>


class File
{
private:
	std::fstream file;

public:

	void readFile(std::fstream file);
	void writeFile(std::fstream file);
	void closeFile(std::fstream file) { file.close(); }

};