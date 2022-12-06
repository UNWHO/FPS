#include "file.h"

void File::readFile(std::fstream file) {

	file.open("파일 경로", std::ios::in);

	char line[256] = { 0, };
	while (file.getline(line, 256)) {
		std::cout << line << std::endl;
	}
}

void File::writeFile(std::fstream file) {
	file.open("파일 경로", std::ios::out | std::ios::app);
}