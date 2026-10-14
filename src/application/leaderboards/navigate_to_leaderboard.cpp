#include "navigate_to_leaderboard.hpp"

NavigateToLeaderboard::NavigateToLeaderboard(LeaderboardRepository &repo, LeaderboardPresenter &presenter)
    : repo_(repo), presenter_(presenter)
{
}

void NavigateToLeaderboard::Execute()
{
    std::vector<std::string> mapNames = repo_.LoadAllLeaderboardMapNames();
    std::map<std::string, std::vector<LeaderboardEntry>> entriesMap;

    for (const auto &name : mapNames)
    {
        entriesMap[name] = repo_.LoadMapLeaderboard(name);
    }

    presenter_.PresentLeaderboard(mapNames, entriesMap);
}