#pragma once
#include "domain/bonuses/bonus.hpp"
#include <vector>

class BonusStore
{
public:
    BonusStore();
    std::vector<Bonus> GetAll();
    void Add(Bonus bonus);
    void Change(int id, Bonus bonus);
    void Remove(int id);
};