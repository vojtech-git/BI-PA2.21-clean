#pragma once

#include <vector>

#include "domain/boards/board.hpp"
#include "domain/bombs/bomb.hpp"
#include "domain/common/position.hpp"
#include "domain/walls/wall.hpp"

class CollisionService {
public:
    static bool IsTileBlockedForPlayer(
        Position position,
        const Board &board,
        const std::vector<Wall> &walls,
        const std::vector<Bomb> &bombs,
        bool is_levitating
    );

    static bool IsTileBlockedForGhost(
        Position position,
        const Board &board,
        const std::vector<Wall> &walls,
        const std::vector<Bomb> &bombs
    );

private:
    static bool HasWallCollision(
        Position position,
        const std::vector<Wall> &walls,
        bool allow_soft_walls
    );

    static bool HasBombCollision(
        Position position,
        const std::vector<Bomb> &bombs
    );
};