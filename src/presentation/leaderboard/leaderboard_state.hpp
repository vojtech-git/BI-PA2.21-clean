#pragma once
#include "application/leaderboards/leaderboard_entry.hpp"
#include <string>
#include <vector>
#include <map>

struct LeaderboardState
{
    int currentMapIndex{0};
    std::vector<std::string> mapNames;
    std::map<std::string, std::vector<LeaderboardEntry>> cachedEntries;
};