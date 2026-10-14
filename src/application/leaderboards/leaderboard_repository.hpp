#pragma once
#include "leaderboard_entry.hpp"
#include <vector>
#include <string>

class LeaderboardRepository
{
public:
    virtual ~LeaderboardRepository() = default;
    virtual std::vector<std::string> LoadAllLeaderboardMapNames() = 0;
    virtual std::vector<LeaderboardEntry> LoadMapLeaderboard(const std::string &mapName) = 0;
};