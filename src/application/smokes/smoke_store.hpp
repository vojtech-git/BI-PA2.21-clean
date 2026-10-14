#pragma once
#include "domain/smokes/smoke.hpp"
#include <vector>

class SmokeStore
{
public:
    SmokeStore();
    std::vector<Smoke> GetAll();
    void Add(Smoke smoke);
    void Change(int id, Smoke smoke);
    void Remove(int id);
};