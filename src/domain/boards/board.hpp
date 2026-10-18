#pragma once

#include <cstdint>
#include "domain/common/position.hpp"
#include "domain/boards/bonus_chances.hpp"

class Board {
public:
    Board(uint32_t width, uint32_t height, BonusChances bonus_chances);

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    const BonusChances& GetBonusChances() const;
    bool IsInBounds(Position position) const;

private:
    uint32_t width_;
    uint32_t height_;
    BonusChances bonus_chances_;
};