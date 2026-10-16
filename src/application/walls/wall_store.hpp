#pragma once
#include "domain/walls/wall.hpp"
#include <vector>

class WallStore
{
public:
    WallStore() = default;
    ~WallStore() = default;

    const std::vector<Wall>& GetAll() const { return walls_; }
    void Add(const Wall &wall) { walls_.push_back(wall); }
    void Clear() { walls_.clear(); }
    bool RemoveAt(size_t x, size_t y);
    const Wall* GetAt(size_t x, size_t y) const;

private:
    std::vector<Wall> walls_;
};