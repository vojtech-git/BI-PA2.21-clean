#pragma once
#include "application/players/player_store.hpp"

class TickPlayers {
public:
    explicit TickPlayers(PlayerStore &player_store);
    void Execute(float dt);

private:
    PlayerStore &player_store_;
};