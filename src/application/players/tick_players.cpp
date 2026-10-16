#include "tick_players.hpp"

TickPlayers::TickPlayers(PlayerStore &player_store)
    : player_store_(player_store) {}

void TickPlayers::Execute(float dt) {
    for (auto &player : player_store_.GetAllMutable()) {
        if (!player.IsDead()) {
            player.UpdateCooldown(dt);
        }
    }
}