#pragma once
#include "application/common/repository.hpp"
#include "domain/walls/wall.hpp"

class WallRepository : public IRepository<Wall, WallId> {
public:
    virtual std::optional<Wall> GetAt(uint32_t x, uint32_t y) const = 0;
    virtual bool DeleteAt(uint32_t x, uint32_t y) = 0;
};