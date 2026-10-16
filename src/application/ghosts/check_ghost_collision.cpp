#include "check_ghost_collision.hpp"

CheckGhostCollision::CheckGhostCollision(
    PlayerStore &player_store,
    GhostStore &ghost_store,
    GhostCollisionPresenter &presenter
) : player_store_(player_store),
    ghost_store_(ghost_store),
    presenter_(presenter) {}

void CheckGhostCollision::Execute() {
    auto &players = player_store_.GetAllMutable();
    const auto &ghosts = ghost_store_.GetAll();

    for (size_t i = 0; i < players.size(); ++i) {
        auto &player = players[i];
        if (player.IsDead()) continue;

        for (const auto &ghost : ghosts) {
            if (player.GetX() == ghost.GetX() && player.GetY() == ghost.GetY()) {
                player.TakeDamage(1);
                int player_id = static_cast<int>(i);

                if (player.IsDead()) {
                    presenter_.PresentPlayerDied(player_id, player.GetX(), player.GetY());
                } else {
                    presenter_.PresentPlayerDamaged(player_id, player.GetHealth());
                }
                break;
            }
        }
    }
}