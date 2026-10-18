#include "domain/boards/board.hpp"

Board::Board(
    uint32_t width,
    uint32_t height,
    bool flame_chance,
    bool frozen_chance,
    bool levitation_chance,
    bool delay_chance,
    bool health_chance
) : width_(width),
    height_(height),
    flame_chance_(flame_chance),
    frozen_chance_(frozen_chance),
    levitation_chance_(levitation_chance),
    delay_chance_(delay_chance),
    health_chance_(health_chance) {}

uint32_t Board::GetWidth() const {
    return width_;
}

uint32_t Board::GetHeight() const {
    return height_;
}

bool Board::IsInBounds(Position position) const {
    return position.x < width_ && position.y < height_;
}

bool Board::HasFlameChance() const {
    return flame_chance_;
}

bool Board::HasFrozenChance() const {
    return frozen_chance_;
}

bool Board::HasLevitationChance() const {
    return levitation_chance_;
}

bool Board::HasDelayChance() const {
    return delay_chance_;
}

bool Board::HasHealthChance() const {
    return health_chance_;
}

float Board::GetElapsedTime() const {
    return elapsed_time_;
}

bool Board::IsGameOver() const {
    return is_game_over_;
}

void Board::UpdateTimer(float dt) {
    if (!is_game_over_) {
        elapsed_time_ += dt;
    }
}

void Board::MarkGameOver() {
    is_game_over_ = true;
}