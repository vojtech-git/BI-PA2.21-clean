#include "domain/boards/board.hpp"

Board::Board(uint32_t width, uint32_t height, BonusChances bonus_chances)
    : width_(width),
      height_(height),
      bonus_chances_(bonus_chances) {}

uint32_t Board::GetWidth() const {
    return width_;
}

uint32_t Board::GetHeight() const {
    return height_;
}

const BonusChances& Board::GetBonusChances() const {
    return bonus_chances_;
}

bool Board::IsInBounds(Position position) const {
    return position.x < width_ && position.y < height_;
}