#pragma once
#include "presentation/view.hpp"
#include "presentation/app_state.hpp"
#include "leaderboard_state.hpp"
#include "application/leaderboards/leaderboard_presenter.hpp"
#include <string>
#include <vector>
#include <map>

class CursesLeaderboardPresenter : public LeaderboardPresenter
{
public:
    CursesLeaderboardPresenter(View &view, AppState &app_state);

    void PresentLeaderboard(
        const std::vector<std::string> &mapNames,
        const std::map<std::string, std::vector<LeaderboardEntry>> &entries) override;
    void ChangePage(int delta);

private:
    void Render();

    View &view_;
    AppState &app_state_;
    LeaderboardState state_;
};