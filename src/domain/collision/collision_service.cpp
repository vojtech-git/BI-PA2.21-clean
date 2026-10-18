#include "domain/collision/collision_service.hpp"

bool CollisionService::IsTileBlockedForPlayer(
    Position position,
    const Board &board,
    const std::vector<Wall> &walls,
    const std::vector<Bomb> &bombs,
    bool is_levitating
) {
    if (!board.IsInBounds(position)) {
        return true;
    }

    if (HasWallCollision(position, walls, is_levitating)) {
        return true;
    }

    return HasBombCollision(position, bombs);
}

bool CollisionService::IsTileBlockedForGhost(
    Position position,
    const Board &board,
    const std::vector<Wall> &walls,
    const std::vector<Bomb> &bombs
) {
    if (!board.IsInBounds(position)) {
        return true;
    }

    if (HasWallCollision(position, walls, false)) {
        return true;
    }

    return HasBombCollision(position, bombs);
}

bool CollisionService::HasWallCollision(
    Position position,
    const std::vector<Wall> &walls,
    bool allow_soft_walls
) {
    for (const auto &wall : walls) {
        if (wall.GetPosition() == position) {
            if (wall.GetType() == WallType::Hard || !allow_soft_walls) {
                return true;
            }
        }
    }
    return false;
}

bool CollisionService::HasBombCollision(
    Position position,
    const std::vector<Bomb> &bombs
) {
    for (const auto &bomb : bombs) {
        if (bomb.GetPosition() == position) {
            return true;
        }
    }
    return false;
}