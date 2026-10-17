#include "domain/walls/wall.hpp"

Wall::Wall(WallId id, uint32_t x_position, uint32_t y_position, WallType type)
    : id_(id),
      x_position_(x_position),
      y_position_(y_position),
      type_(type) {}