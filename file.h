#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class File
{
public:
	static std::vector<std::string> read(std::string path)
	{
		std::ifstream stream;
		stream.open(path, std::ios::in);
		
		if (stream.fail())
		{
			std::cout << "Failed to open file : " + path;
			return std::vector<std::string>();
		}

		char buf[1024];
		std::vector<std::string> result;

		while (stream.getline(buf, 1024))
		{
			result.push_back(std::string(buf));
		}

		stream.close();

		return result;
	}

	static void write(std::string path, const std::vector<std::string> contents)
	{
		std::ofstream stream = std::ofstream(path);
		if (stream.fail())
		{
			std::cout << "Failed to write file : " + path;
			return;
		}

		for (auto iter = contents.begin(); iter != contents.end(); iter++)
		{
			stream << *iter << std::endl;
		}

		stream.close();
		return;
	}
};