#include "curses_map_select_presenter.hpp"
#include <algorithm>

CursesMapSelectPresenter::CursesMapSelectPresenter(View &view, AppState &app_state)
    : view_(view), app_state_(app_state) {}

void CursesMapSelectPresenter::PresentMapSelect(const std::vector<std::string> &maps) {
    state_.maps = maps;
    state_.currentPage = 0;
    state_.totalPages = std::max(1, static_cast<int>((maps.size() + 3) / 4));
    app_state_ = AppState::MapSelect;
    Render();
}

void CursesMapSelectPresenter::PresentSelectedMap(const std::string &mapName) {
    state_.selectedMap = mapName;
    Render();
}

void CursesMapSelectPresenter::ChangePage(int delta) {
    int next = state_.currentPage + delta;
    if (next >= 0 && next < state_.totalPages) {
        state_.currentPage = next;
        Render();
    }
}

std::optional<std::string> CursesMapSelectPresenter::GetMapAtSlot(int slotIndex) const {
    if (slotIndex < 0 || slotIndex >= 4) {
        return std::nullopt;
    }
    size_t targetIndex = static_cast<size_t>(state_.currentPage) * 4 + static_cast<size_t>(slotIndex);
    if (targetIndex < state_.maps.size()) {
        return state_.maps[targetIndex];
    }
    return std::nullopt;
}

void CursesMapSelectPresenter::Render() {
    view_.ClearScreen();
    int centerX = view_.GetWidth() / 2;
    view_.DrawText(centerX, 2, "MAP SELECTION");
    view_.DrawText(centerX, view_.GetHeight() - 2, "[Arrows: Page | 1-4: Select | Q: Back]");

    std::string selText = "Selected: " + (state_.selectedMap.empty() ? "None" : state_.selectedMap);
    view_.DrawText(centerX, 4, selText);

    size_t startIndex = static_cast<size_t>(state_.currentPage) * 4;
    int startY = 7;
    for (size_t i = 0; i < 4; ++i) {
        int lineY = startY + static_cast<int>(i) * 2;
        size_t mapIdx = startIndex + i;
        std::string label;
        if (mapIdx < state_.maps.size()) {
            label = "(" + std::to_string(i + 1) + ") " + state_.maps[mapIdx];
        } else {
            label = "(" + std::to_string(i + 1) + ") ---";
        }
        view_.DrawText(centerX, lineY, label);
    }

    int counterY = view_.GetHeight() - 4;
    std::string pageIndicator = "< " + std::to_string(state_.currentPage + 1) + " / " + std::to_string(state_.totalPages) + " >";
    view_.DrawText(centerX, counterY, pageIndicator);
    view_.Render();
}