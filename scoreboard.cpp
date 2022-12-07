#include "scoreboard.h"

// open->write->read->sort->close
void Scoreboard::manageFile(std::fstream file, std::pair<std::string, float>const& player) {
    file.open("scoreboard.txt", std::ios::app);

    std::string player_name = player.first;
    float player_clearTime = player.second;

    if (file.is_open()) {
        file << player.first << " " << player.second << std::endl;

        std::vector<std::pair<std::string, float>> name_clearTime;

        std::string name;
        float clearTime;

        while (file >> name >> clearTime) { name_clearTime.push_back(std::make_pair(name, clearTime)); }

        std::sort(name_clearTime.begin(), name_clearTime.end());

        int rank = 1;
        for (auto it = name_clearTime.begin(); it != name_clearTime.end(); ++it) {
            file << it->first << " " << it->second << std::endl;
            rank++;
        }

        file.close();
    }
}

bool Scoreboard::compareNameTime(std::pair<std::string, float>const& a, std::pair<std::string, float>const& b) {
	if (a.second == b.second) 
        return a.first < b.first;
	else
        return a.second < b.second;
}