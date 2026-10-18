#pragma once

#include "domain/ghosts/ghost.hpp"
#include "domain/maps/map.hpp"
#include "domain/walls/wall.hpp"
#include "domain/bombs/bomb.hpp"
#include "domain/common/position.hpp"
#include <optional>
#include <vector>

class GhostMovementService {
public:
    static std::optional<Position> CalculateNextPosition(
        const Ghost &ghost,
        const Map &map,
        const std::vector<Wall> &walls,
        const std::vector<Bomb> &bombs
    );

private:
    static std::vector<Position> GetValidNeighborMoves(
        const Ghost &ghost,
        const Map &map,
        const std::vector<Wall> &walls,
        const std::vector<Bomb> &bombs
    );
};