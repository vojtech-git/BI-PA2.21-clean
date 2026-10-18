#include "domain/ghosts/ghost_movement_service.hpp"
#include "domain/collision/collision_service.hpp"
#include <cstdlib>

std::optional<Position> GhostMovementService::CalculateNextPosition(
    const Ghost &ghost,
    const Map &map,
    const std::vector<Wall> &walls,
    const std::vector<Bomb> &bombs
) {
    std::vector<Position> valid_moves = GetValidNeighborMoves(ghost, map, walls, bombs);

    if (valid_moves.empty()) {
        return std::nullopt;
    }

    size_t chosen_idx = static_cast<size_t>(std::rand()) % valid_moves.size();
    return valid_moves[chosen_idx];
}

std::vector<Position> GhostMovementService::GetValidNeighborMoves(
    const Ghost &ghost,
    const Map &map,
    const std::vector<Wall> &walls,
    const std::vector<Bomb> &bombs
) {
    constexpr int dx[] = {0, 0, -1, 1};
    constexpr int dy[] = {-1, 1, 0, 0};

    std::vector<Position> valid_moves;
    valid_moves.reserve(4);

    for (int i = 0; i < 4; ++i) {
        long long target_x = static_cast<long long>(ghost.GetX()) + dx[i];
        long long target_y = static_cast<long long>(ghost.GetY()) + dy[i];

        if (target_x < 0 || target_y < 0) {
            continue;
        }

        uint32_t next_x = static_cast<uint32_t>(target_x);
        uint32_t next_y = static_cast<uint32_t>(target_y);

        if (!CollisionService::IsTileBlockedForGhost(Position{next_x, next_y}, map, walls, bombs)) {
            valid_moves.push_back(Position{next_x, next_y});
        }
    }

    return valid_moves;
}