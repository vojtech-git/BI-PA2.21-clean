#include "controls_view.hpp"

ControlsView::~ControlsView() {
    if (window_) {
        delwin(window_);
        window_ = nullptr;
    }
}

void ControlsView::InitWindow(int y, int x, int width, int height) {
    if (window_) {
        delwin(window_);
    }
    y_ = y;
    x_ = x;
    width_ = width;
    height_ = height;
    window_ = newwin(height_, width_, y_, x_);
}

void ControlsView::SetPosition(int y, int x) {
    y_ = y;
    x_ = x;
    if (window_) {
        mvwin(window_, y_, x_);
    }
}

void ControlsView::SetControls(const std::vector<PlayerControlSummary> &controls) {
    if (!window_) return;
    werase(window_);

    int y = 0;
    for (const auto &ctrl : controls) {
        std::string line = ctrl.name + ": Move [" + ctrl.moveKeys + "] | Bomb [" + ctrl.bombKey + "]";
        int start_x = (width_ - static_cast<int>(line.length())) / 2;
        if (start_x < 1) start_x = 1;
        mvwprintw(window_, y++, start_x, "%s", line.c_str());
    }

    std::string back_prompt = "[Q: Back to Menu]";
    int back_x = (width_ - static_cast<int>(back_prompt.length())) / 2;
    if (back_x < 1) back_x = 1;
    mvwprintw(window_, y, back_x, "%s", back_prompt.c_str());
}

void ControlsView::StageRender() {
    if (window_) {
        wnoutrefresh(window_);
    }
}

void ControlsView::ClearWindow() {
    if (window_) {
        werase(window_);
        wnoutrefresh(window_);
        delwin(window_);
        window_ = nullptr;
    }
}