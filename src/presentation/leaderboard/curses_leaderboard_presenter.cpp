#include "curses_leaderboard_presenter.hpp"

CursesLeaderboardPresenter::CursesLeaderboardPresenter(View &view, AppState &app_state)
    : view_(view), app_state_(app_state)
{
}

void CursesLeaderboardPresenter::PresentLeaderboard(
    const std::vector<std::string> &mapNames,
    const std::map<std::string, std::vector<LeaderboardEntry>> &entries)
{
    state_.mapNames = mapNames;
    state_.cachedEntries = entries;
    state_.currentMapIndex = 0;

    app_state_ = AppState::Leaderboard;
    Render();
}

void CursesLeaderboardPresenter::ChangePage(int delta)
{
    if (state_.mapNames.empty())
    {
        return;
    }

    int nextIndex = state_.currentMapIndex + delta;
    if (nextIndex >= 0 && nextIndex < static_cast<int>(state_.mapNames.size()))
    {
        state_.currentMapIndex = nextIndex;
        Render();
    }
}

void CursesLeaderboardPresenter::Render()
{
    view_.ClearScreen();

    int centerX = view_.GetWidth() / 2;
    view_.DrawText(centerX, 2, "LEADERBOARDS");
    view_.DrawText(centerX, view_.GetHeight() - 2, "[Arrows: Map | Q: Back]");

    std::string currentMap = state_.mapNames.empty() ? "None" : state_.mapNames[state_.currentMapIndex];
    view_.DrawText(centerX, 4, "Map: " + currentMap);

    std::vector<LeaderboardEntry> entries;
    if (!state_.mapNames.empty() && state_.cachedEntries.count(currentMap))
    {
        entries = state_.cachedEntries[currentMap];
    }

    int startY = 7;
    for (size_t i = 0; i < 4; ++i)
    {
        int lineY = startY + static_cast<int>(i) * 2;
        std::string label;
        if (i < entries.size())
        {
            label = std::to_string(i + 1) + ". " + entries[i].playerName + " - " + std::to_string(entries[i].score);
        }
        else
        {
            label = std::to_string(i + 1) + ". ---";
        }
        view_.DrawText(centerX, lineY, label);
    }

    int counterY = view_.GetHeight() - 4;
    int totalMaps = static_cast<int>(state_.mapNames.size());
    std::string indicator = "< " + std::to_string(totalMaps == 0 ? 0 : state_.currentMapIndex + 1) +
                           " / " + std::to_string(totalMaps) + " >";
    view_.DrawText(centerX, counterY, indicator);

    view_.Render();
}