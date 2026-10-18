#include "application/players/tick_players.hpp"

TickPlayers::TickPlayers(PlayerRepository &player_repo)
    : player_repo_(player_repo) {}

void TickPlayers::Execute(float dt) {
    auto players = player_repo_.GetAll();

    for (auto &player : players) {
        if (!player.IsDead()) {
            player.UpdateCooldown(dt);
            player.UpdateInvulnerability(dt);
            player.UpdateFreeze(dt);
            player.UpdateLevitation(dt);
            player_repo_.Save(player);
        }
    }
}