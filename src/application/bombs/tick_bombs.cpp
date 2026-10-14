#include "tick_bombs.hpp"

TickBombs::TickBombs(BombStore bomb_store)
{
    bomb_store_ = bomb_store;
}

void TickBombs::Execute()
{
    // gets all bombs

    // calculates the explosion timer
    // detonates if ready
    // detonates damaged bombs
    // damages player, ghosts, walls
    // creates the smokes
    // presents the changes

    // if player died present game over
}