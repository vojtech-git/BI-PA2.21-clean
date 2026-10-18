#pragma once
#include "application/common/repository.hpp"
#include "domain/bonuses/bonus.hpp"

class BonusRepository : public virtual IRepository<Bonus, BonusId> {
public:
    virtual std::optional<Bonus> RemoveAt(uint32_t x, uint32_t y) = 0;
};