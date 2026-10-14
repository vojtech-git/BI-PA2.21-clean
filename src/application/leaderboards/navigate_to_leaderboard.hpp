#pragma once
#include "leaderboard_repository.hpp"
#include "leaderboard_presenter.hpp"

class NavigateToLeaderboard
{
public:
    NavigateToLeaderboard(LeaderboardRepository &repo, LeaderboardPresenter &presenter);
    void Execute();

private:
    LeaderboardRepository &repo_;
    LeaderboardPresenter &presenter_;
};