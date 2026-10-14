#pragma once
#include <string>
#include <vector>
#include <cstddef>
#include "domain/walls/wall.hpp"

struct BonusChances {
    bool flame{false};
    bool frozen{false};
    bool levitation{false};
    bool delay{false};
    bool health{false};
};

struct PlayerConfigDto {
    size_t x{0};
    size_t y{0};
    std::string name;
    char upKey{0};
    char leftKey{0};
    char downKey{0};
    char rightKey{0};
    char bombKey{0};
};

struct PositionDto {
    size_t x{0};
    size_t y{0};
};

struct WallDto {
    size_t x{0};
    size_t y{0};
    WallType type;
};

struct MapDto {
    size_t height{0};
    size_t width{0};
    BonusChances bonusChances;
    std::vector<WallDto> walls;
    std::vector<PositionDto> ghosts;
    std::vector<PlayerConfigDto> players;
    PositionDto doorPosition;
    bool hasDoor{false};
};