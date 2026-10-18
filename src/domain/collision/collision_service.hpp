#pragma once

#include "domain/common/position.hpp"
#include "domain/maps/map.hpp"
#include "domain/walls/wall.hpp"
#include "domain/bombs/bomb.hpp"
#include <vector>

class CollisionService {
public:
    static bool IsTileBlockedForPlayer(
        Position position,
        const Map &map,
        const std::vector<Wall> &walls,
        const std::vector<Bomb> &bombs,
        bool is_levitating
    );

    static bool IsTileBlockedForGhost(
        Position position,
        const Map &map,
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