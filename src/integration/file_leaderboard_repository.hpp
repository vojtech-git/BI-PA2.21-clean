#pragma once
#include "application/leaderboards/leaderboard_repository.hpp"

class FileLeaderboardRepository : public LeaderboardRepository
{
public:
    std::vector<std::string> LoadAllLeaderboardMapNames() override;
    std::vector<LeaderboardEntry> LoadMapLeaderboard(const std::string &mapName) override;
    void SaveScore(const std::string &mapName, const LeaderboardEntry &entry) override;
};