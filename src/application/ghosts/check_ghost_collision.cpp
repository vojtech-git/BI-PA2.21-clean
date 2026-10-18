#include "application/ghosts/check_ghost_collision.hpp"

CheckGhostCollision::CheckGhostCollision(
    PlayerRepository &player_repo,
    GhostRepository &ghost_repo,
    GhostCollisionPresenter &presenter
) : player_repo_(player_repo),
    ghost_repo_(ghost_repo),
    presenter_(presenter) {}

void CheckGhostCollision::Execute() {
    auto players = player_repo_.GetAll();
    const auto ghosts = ghost_repo_.GetAll();

    for (auto &player : players) {
        if (player.IsDead()) {
            continue;
        }

        for (const auto &ghost : ghosts) {
            if (player.GetPosition() == ghost.GetPosition()) {
                player.TakeDamage(1);
                player_repo_.Save(player);

                if (player.IsDead()) {
                    presenter_.PresentPlayerDied(player.GetId(), player.GetX(), player.GetY());
                } else {
                    presenter_.PresentPlayerDamaged(player.GetId(), player.GetHealth());
                }
                break;
            }
        }
    }
}