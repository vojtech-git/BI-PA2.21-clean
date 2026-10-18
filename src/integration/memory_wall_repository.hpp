#pragma once
#include "integration/memory_repository.hpp"
#include "application/walls/wall_repository.hpp"

class MemoryWallRepository 
    : public InMemoryRepository<Wall, WallId>,
      public WallRepository {
public:
    std::optional<Wall> GetAt(uint32_t x, uint32_t y) const override {
        for (const auto &[id, wall] : entities_) {
            if (wall.GetX() == x && wall.GetY() == y) {
                return wall;
            }
        }
        return std::nullopt;
    }

    bool DeleteAt(uint32_t x, uint32_t y) override {
        for (auto it = entities_.begin(); it != entities_.end(); ++it) {
            if (it->second.GetX() == x && it->second.GetY() == y) {
                entities_.erase(it);
                return true;
            }
        }
        return false;
    }
};