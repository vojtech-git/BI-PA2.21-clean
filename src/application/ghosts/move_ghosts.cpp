#include "move_ghosts.hpp"
#include <vector>
#include <cstdlib>

MoveGhosts::MoveGhosts(
    GhostStore &ghost_store,
    MapStore &map_store,
    WallStore &wall_store,
    BombStore &bomb_store,
    GhostPresenter &presenter
) : ghost_store_(ghost_store),
    map_store_(map_store),
    wall_store_(wall_store),
    bomb_store_(bomb_store),
    presenter_(presenter) {}

void MoveGhosts::Execute(float dt) {
    auto &ghosts = ghost_store_.GetAllMutable();
    Map map = map_store_.Get();

    const int dx[] = {0, 0, -1, 1};
    const int dy[] = {-1, 1, 0, 0};

    for (auto &ghost : ghosts) {
        ghost.Update(dt);
        if (!ghost.CanMove()) {
            continue;
        }

        size_t gx = ghost.GetX();
        size_t gy = ghost.GetY();

        std::vector<std::pair<size_t, size_t>> valid_moves;

        for (int i = 0; i < 4; ++i) {
            long long target_x = static_cast<long long>(gx) + dx[i];
            long long target_y = static_cast<long long>(gy) + dy[i];

            if (target_x < 0 || target_x >= static_cast<long long>(map.GetWidth()) ||
                target_y < 0 || target_y >= static_cast<long long>(map.GetHeight())) {
                continue;
            }

            size_t tx = static_cast<size_t>(target_x);
            size_t ty = static_cast<size_t>(target_y);

            if (!IsTileBlocked(tx, ty)) {
                valid_moves.push_back({tx, ty});
            }
        }

        if (!valid_moves.empty()) {
            auto [next_x, next_y] = valid_moves[static_cast<size_t>(std::rand()) % valid_moves.size()];
            ghost.Move(next_x, next_y);
            presenter_.PresentGhostMoved(gx, gy, next_x, next_y);
        } else {
            ghost.ResetTimer();
        }
    }
}

bool MoveGhosts::IsTileBlocked(size_t x, size_t y) const {
    for (const auto &wall : wall_store_.GetAll()) {
        if (wall.GetX() == x && wall.GetY() == y) {
            return true;
        }
    }
    for (const auto &bomb : bomb_store_.GetAll()) {
        if (bomb.GetX() == x && bomb.GetY() == y) {
            return true;
        }
    }
    return false;
}