#pragma once

#include "application/players/player_repository.hpp"

class TickPlayers {
public:
    explicit TickPlayers(PlayerRepository &player_repo);
    void Execute(float dt);

private:
    PlayerRepository &player_repo_;
};