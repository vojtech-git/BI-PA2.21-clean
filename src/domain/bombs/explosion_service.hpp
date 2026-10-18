#pragma once

#include "domain/bombs/bomb.hpp"
#include "domain/maps/map.hpp"
#include "domain/walls/wall.hpp"
#include "domain/players/player.hpp"
#include "domain/ghosts/ghost.hpp"
#include "domain/common/position.hpp"
#include "domain/common/entity_id.hpp"

#include <vector>

struct ExplosionOutcome {
    std::vector<Position> smoke_tiles;
    std::vector<Position> destroyed_wall_tiles;
    std::vector<Player> affected_players;
    std::vector<GhostId> killed_ghost_ids;
};

class ExplosionDomainService {
public:
    static ExplosionOutcome ProcessExplosion(
        const Bomb &bomb,
        const Map &map,
        const std::vector<Wall> &walls,
        std::vector<Player> players,
        const std::vector<Ghost> &ghosts
    );

private:
    static void ApplyDamageAt(
        Position pos,
        std::vector<Player> &players,
        const std::vector<Ghost> &ghosts,
        ExplosionOutcome &outcome
    );
};