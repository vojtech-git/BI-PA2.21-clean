#pragma once
#include "integration/memory_repository.hpp"
#include "application/bonuses/bonus_repository.hpp"

class MemoryBonusRepository 
    : public InMemoryRepository<Bonus, BonusId>,
      public BonusRepository {
public:
    std::optional<Bonus> RemoveAt(uint32_t x, uint32_t y) override {
        for (auto it = entities_.begin(); it != entities_.end(); ++it) {
            if (it->second.GetX() == x && it->second.GetY() == y) {
                Bonus removed = it->second;
                entities_.erase(it);
                return removed;
            }
        }
        return std::nullopt;
    }
};