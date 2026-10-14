#pragma once

#include "domain/bombs/bomb.hpp"
#include <vector>

class BombStore {
public:
    BombStore() = default;
    ~BombStore() = default;

    const std::vector<Bomb>& GetAll() const;
    void Add(const Bomb &bomb);
    void Remove(size_t index);
    void Clear();

private:
    std::vector<Bomb> bombs_;
};