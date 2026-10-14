#pragma once
#include "bomb_store.hpp"

class TickBombs
{
public:
    TickBombs(BombStore bomb_store);
    void Execute();

private:
    BombStore bomb_store_;
};