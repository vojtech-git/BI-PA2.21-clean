#pragma once
#include "leaderboard_entry.hpp"
#include <map>
#include <string>
#include <vector>

class LeaderboardPresenter
{
public:
    virtual ~LeaderboardPresenter() = default;
    virtual void PresentLeaderboard(
        const std::vector<std::string> &mapNames,
        const std::map<std::string, std::vector<LeaderboardEntry>> &entries) = 0;
};