#pragma once

#include <optional>
#include <vector>

#include "domain/boards/board.hpp"
#include "domain/bombs/bomb.hpp"
#include "domain/common/position.hpp"
#include "domain/ghosts/ghost.hpp"
#include "domain/walls/wall.hpp"

class GhostMovementService {
public:
    static std::optional<Position> CalculateNextPosition(
        const Ghost &ghost,
        const Board &board,
        const std::vector<Wall> &walls,
        const std::vector<Bomb> &bombs
    );

private:
    static std::vector<Position> GetValidNeighborMoves(
        const Ghost &ghost,
        const Board &board,
        const std::vector<Wall> &walls,
        const std::vector<Bomb> &bombs
    );
};