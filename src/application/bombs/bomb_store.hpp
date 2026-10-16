#pragma once
#include "domain/bombs/bomb.hpp"
#include <vector>
#include <cstddef>

class BombStore {
public:
    BombStore() = default;
    ~BombStore() = default;

    const std::vector<Bomb>& GetAll() const;
    std::vector<Bomb>& GetAllMutable();
    void Add(const Bomb &bomb);
    void Remove(size_t index);
    void Clear();

private:
    std::vector<Bomb> bombs_;
};