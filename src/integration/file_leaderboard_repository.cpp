#include "file_leaderboard_repository.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>

std::vector<std::string> FileLeaderboardRepository::LoadAllLeaderboardMapNames()
{
    std::vector<std::string> names;
    const std::string dir = "leaderboards";
    if (std::filesystem::exists(dir))
    {
        for (const auto &entry : std::filesystem::directory_iterator(dir))
        {
            if (entry.is_regular_file())
            {
                names.push_back(entry.path().stem().string());
            }
        }
    }
    return names;
}

std::vector<LeaderboardEntry> FileLeaderboardRepository::LoadMapLeaderboard(const std::string &mapName)
{
    std::vector<LeaderboardEntry> entries;
    std::string filePath = "leaderboards/" + mapName;
    if (filePath.find(".txt") == std::string::npos)
    {
        filePath += ".txt";
    }

    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return entries;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        std::istringstream iss(line);
        std::string name;
        int score = 0;
        if (iss >> name >> score)
        {
            entries.push_back({name, score});
        }
    }

    std::sort(entries.begin(), entries.end(), [](const LeaderboardEntry &a, const LeaderboardEntry &b) {
        return a.score > b.score;
    });

    return entries;
}