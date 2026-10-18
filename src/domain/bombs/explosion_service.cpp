#include "domain/bombs/explosion_service.hpp"
#include <algorithm>

ExplosionOutcome ExplosionDomainService::ProcessExplosion(
    const Bomb &bomb,
    const Map &map,
    const std::vector<Wall> &walls,
    std::vector<Player> players,
    const std::vector<Ghost> &ghosts
) {
    ExplosionOutcome outcome;
    outcome.smoke_tiles.push_back(bomb.GetPosition());

    ApplyDamageAt(bomb.GetPosition(), players, ghosts, outcome);

    const int dx[] = {0, 0, -1, 1};
    const int dy[] = {-1, 1, 0, 0};

    for (int dir = 0; dir < 4; ++dir) {
        for (uint32_t step = 1; step <= bomb.GetExplosionSize(); ++step) {
            long long tx = static_cast<long long>(bomb.GetX()) + dx[dir] * step;
            long long ty = static_cast<long long>(bomb.GetY()) + dy[dir] * step;

            if (tx < 0 || ty < 0 || !map.IsInBounds(static_cast<uint32_t>(tx), static_cast<uint32_t>(ty))) {
                break;
            }

            Position pos{static_cast<uint32_t>(tx), static_cast<uint32_t>(ty)};

            auto wall_it = std::find_if(walls.begin(), walls.end(), [&](const Wall &w) {
                return w.GetPosition() == pos;
            });

            if (wall_it != walls.end()) {
                if (wall_it->GetType() == WallType::Hard) {
                    break;
                }
                outcome.destroyed_wall_tiles.push_back(pos);
                outcome.smoke_tiles.push_back(pos);
                ApplyDamageAt(pos, players, ghosts, outcome);
                break;
            }

            outcome.smoke_tiles.push_back(pos);
            ApplyDamageAt(pos, players, ghosts, outcome);
        }
    }

    return outcome;
}

void ExplosionDomainService::ApplyDamageAt(
    Position pos,
    std::vector<Player> &players,
    const std::vector<Ghost> &ghosts,
    ExplosionOutcome &outcome
) {
    for (auto &player : players) {
        if (!player.IsDead() && player.GetPosition() == pos) {
            player.TakeDamage(1);
            outcome.affected_players.push_back(player);
        }
    }

    for (const auto &ghost : ghosts) {
        if (ghost.GetPosition() == pos) {
            outcome.killed_ghost_ids.push_back(ghost.GetId());
        }
    }
}