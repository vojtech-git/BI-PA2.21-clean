#include "board_view.hpp"

BoardView::~BoardView() {
    if (window_) {
        delwin(window_);
        window_ = nullptr;
    }
}

void BoardView::InitWindow(int y, int x, size_t width, size_t height) {
    if (window_) {
        delwin(window_);
    }
    y_ = y;
    x_ = x;
    width_ = width;
    height_ = height;
    window_ = newwin(static_cast<int>(height_), static_cast<int>(width_), y_, x_);

    TileLayers empty_tile{};
    empty_tile.fill(0);
    grid_.assign(height_, std::vector<TileLayers>(width_, empty_tile));
}

void BoardView::Clear() {
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            grid_[y][x].fill(0);
            UpdateCell(x, y);
        }
    }
}

void BoardView::SetPosition(int y, int x) {
    y_ = y;
    x_ = x;
    if (window_) {
        mvwin(window_, y_, x_);
    }
}

bool BoardView::IsInBounds(size_t x, size_t y) const {
    return y < height_ && x < width_;
}

void BoardView::UpdateCell(size_t x, size_t y) {
    if (!window_ || !IsInBounds(x, y)) return;
    char ch = GetTopChar(x, y);
    mvwaddch(window_, static_cast<int>(y), static_cast<int>(x), ch);
}

void BoardView::AddEntity(size_t x, size_t y, EntityVisualLayer layer) {
    if (IsInBounds(x, y)) {
        grid_[y][x][static_cast<size_t>(layer)]++;
        UpdateCell(x, y);
    }
}

void BoardView::RemoveEntity(size_t x, size_t y, EntityVisualLayer layer) {
    if (IsInBounds(x, y)) {
        auto &count = grid_[y][x][static_cast<size_t>(layer)];
        if (count > 0) {
            count--;
            UpdateCell(x, y);
        }
    }
}

void BoardView::MoveEntity(size_t old_x, size_t old_y, size_t new_x, size_t new_y, EntityVisualLayer layer) {
    RemoveEntity(old_x, old_y, layer);
    AddEntity(new_x, new_y, layer);
}

char BoardView::GetTopChar(size_t x, size_t y) const {
    if (!IsInBounds(x, y)) return ' ';
    const auto &tile = grid_[y][x];

    if (tile[static_cast<size_t>(EntityVisualLayer::Player)] > 0)   return '+';
    if (tile[static_cast<size_t>(EntityVisualLayer::Ghost)] > 0)    return 'G';
    if (tile[static_cast<size_t>(EntityVisualLayer::Bomb)] > 0)     return 'O';
    if (tile[static_cast<size_t>(EntityVisualLayer::Smoke)] > 0)    return '*';
    if (tile[static_cast<size_t>(EntityVisualLayer::Bonus)] > 0)    return '$';
    if (tile[static_cast<size_t>(EntityVisualLayer::Door)] > 0)     return 'D';
    if (tile[static_cast<size_t>(EntityVisualLayer::SoftWall)] > 0) return '=';
    if (tile[static_cast<size_t>(EntityVisualLayer::HardWall)] > 0) return '#';

    return ' ';
}

void BoardView::StageRender() {
    if (window_) {
        wnoutrefresh(window_);
    }
}

void BoardView::ClearWindow() {
    if (window_) {
        werase(window_);
        wnoutrefresh(window_);
        delwin(window_);
        window_ = nullptr;
    }
}