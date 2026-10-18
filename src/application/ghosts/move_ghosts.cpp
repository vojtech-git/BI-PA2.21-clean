#include "application/ghosts/move_ghosts.hpp"
#include "domain/ghosts/ghost_movement_service.hpp"

MoveGhosts::MoveGhosts(
    GhostRepository &ghost_repo,
    BoardRepository &board_repo,
    WallRepository &wall_repo,
    BombRepository &bomb_repo,
    GhostPresenter &presenter
) : ghost_repo_(ghost_repo),
    board_repo_(board_repo),
    wall_repo_(wall_repo),
    bomb_repo_(bomb_repo),
    presenter_(presenter) {}

void MoveGhosts::Execute(float dt) {
    auto board_opt = board_repo_.Get();
    if (!board_opt.has_value()) {
        return;
    }

    auto ghosts = ghost_repo_.GetAll();
    if (ghosts.empty()) {
        return;
    }

    const auto walls = wall_repo_.GetAll();
    const auto bombs = bomb_repo_.GetAll();

    for (auto &ghost : ghosts) {
        ghost.Update(dt);
        if (!ghost.CanMove()) {
            ghost_repo_.Save(ghost);
            continue;
        }

        uint32_t old_x = ghost.GetX();
        uint32_t old_y = ghost.GetY();

        auto next_pos = GhostMovementService::CalculateNextPosition(
            ghost,
            *board_opt,
            walls,
            bombs
        );

        if (next_pos.has_value()) {
            ghost.Move(*next_pos);
            ghost_repo_.Save(ghost);
            presenter_.PresentGhostMoved(old_x, old_y, next_pos->x, next_pos->y);
        } else {
            ghost.ResetTimer();
            ghost_repo_.Save(ghost);
        }
    }
}