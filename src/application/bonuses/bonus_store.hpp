#pragma once
#include "domain/bonuses/bonus.hpp"
#include <vector>
#include <optional>
#include <cstddef>

class BonusStore {
public:
    BonusStore() = default;
    ~BonusStore() = default;

    const std::vector<Bonus>& GetAll() const;
    std::vector<Bonus>& GetAllMutable();
    void Add(const Bonus &bonus);
    bool RemoveAt(size_t x, size_t y, Bonus *removed_bonus = nullptr);
    void Clear();

private:
    std::vector<Bonus> bonuses_;
};