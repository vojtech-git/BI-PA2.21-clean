#include "game_board_buffer.hpp"

void GameBoardBuffer::Resize(size_t width, size_t height) {
    width_ = width;
    height_ = height;
    TileLayers empty_tile{};
    empty_tile.fill(0);
    grid_.assign(height_, std::vector<TileLayers>(width_, empty_tile));
}

void GameBoardBuffer::Clear() {
    for (auto &row : grid_) {
        for (auto &tile : row) {
            tile.fill(0);
        }
    }
}

bool GameBoardBuffer::IsInBounds(size_t x, size_t y) const {
    return y < height_ && x < width_;
}

void GameBoardBuffer::AddEntity(size_t x, size_t y, EntityVisualLayer layer) {
    if (IsInBounds(x, y)) {
        grid_[y][x][static_cast<size_t>(layer)]++;
    }
}

void GameBoardBuffer::RemoveEntity(size_t x, size_t y, EntityVisualLayer layer) {
    if (IsInBounds(x, y)) {
        auto &count = grid_[y][x][static_cast<size_t>(layer)];
        if (count > 0) {
            count--;
        }
    }
}

void GameBoardBuffer::MoveEntity(size_t old_x, size_t old_y, size_t new_x, size_t new_y, EntityVisualLayer layer) {
    RemoveEntity(old_x, old_y, layer);
    AddEntity(new_x, new_y, layer);
}

char GameBoardBuffer::GetTopChar(size_t x, size_t y) const {
    if (!IsInBounds(x, y)) return ' ';

    const auto &tile = grid_[y][x];

    // Priority order: Player > Ghost > Bomb > Smoke > Bonus > Door > SoftWall > HardWall
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

size_t GameBoardBuffer::GetWidth() const { return width_; }
size_t GameBoardBuffer::GetHeight() const { return height_; }