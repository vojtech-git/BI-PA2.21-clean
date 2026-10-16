#pragma once
#include "curses_wrapper.hpp"
#include "application/games/game_hud_state.hpp"
#include <vector>

class ControlsView {
public:
    ControlsView() = default;
    ~ControlsView();

    void InitWindow(int y, int x, int width, int height);
    void SetControls(const std::vector<PlayerControlSummary> &controls);
    void SetPosition(int y, int x);
    void StageRender();
    void ClearWindow();

    int GetHeight() const { return height_; }
    int GetY() const { return y_; }

private:
    WINDOW *window_{nullptr};
    int y_{0};
    int x_{0};
    int width_{0};
    int height_{0};
};