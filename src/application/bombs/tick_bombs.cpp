#include "tick_bombs.hpp"
#include <cstdlib>

TickBombs::TickBombs(
    BombStore &bomb_store,
    MapStore &map_store,
    WallStore &wall_store,
    PlayerStore &player_store,
    GhostStore &ghost_store,
    SmokeStore &smoke_store,
    BonusStore &bonus_store,
    BombPresenter &presenter,
    BonusPresenter &bonus_presenter
) : bomb_store_(bomb_store),
    map_store_(map_store),
    wall_store_(wall_store),
    player_store_(player_store),
    ghost_store_(ghost_store),
    smoke_store_(smoke_store),
    bonus_store_(bonus_store),
    presenter_(presenter),
    bonus_presenter_(bonus_presenter) {}

void TickBombs::Execute(float dt) {
    auto &bombs = bomb_store_.GetAllMutable();
    if (bombs.empty()) return;

    for (size_t i = bombs.size(); i > 0; --i) {
        size_t idx = i - 1;
        bombs[idx].UpdateExplosion(dt);

        if (bombs[idx].GetDetonationTimer() <= 0.0f) {
            Explode(idx);
        }
    }
}

void TickBombs::CheckDamageTile(size_t x, size_t y) {
    auto &players = player_store_.GetAllMutable();
    for (size_t i = 0; i < players.size(); ++i) {
        auto &p = players[i];
        if (p.IsDead()) continue;

        if (p.GetX() == x && p.GetY() == y) {
            p.TakeDamage(1);
            int player_id = static_cast<int>(i);

            if (p.IsDead()) {
                presenter_.PresentPlayerDied(player_id, x, y);
            } else {
                presenter_.PresentPlayerDamaged(player_id, p.GetHealth());
            }
        }
    }

    while (ghost_store_.RemoveAt(x, y)) {
        presenter_.PresentGhostDied(x, y);
    }
}

void TickBombs::Explode(size_t bomb_index) {
    Bomb bomb = bomb_store_.GetAll()[bomb_index];
    bomb_store_.Remove(bomb_index);
    presenter_.PresentBombExploded(bomb.GetX(), bomb.GetY());

    smoke_store_.Add(Smoke(bomb.GetX(), bomb.GetY(), 1));
    presenter_.PresentSmokePlaced(bomb.GetX(), bomb.GetY());
    CheckDamageTile(bomb.GetX(), bomb.GetY());

    const int dx[] = {0, 0, -1, 1};
    const int dy[] = {-1, 1, 0, 0};

    Map map = map_store_.Get();

    for (int dir = 0; dir < 4; ++dir) {
        for (size_t step = 1; step <= bomb.GetExplosionSize(); ++step) {
            long long target_x = static_cast<long long>(bomb.GetX()) + dx[dir] * step;
            long long target_y = static_cast<long long>(bomb.GetY()) + dy[dir] * step;

            if (target_x < 0 || target_x >= static_cast<long long>(map.GetWidth()) ||
                target_y < 0 || target_y >= static_cast<long long>(map.GetHeight())) {
                break;
            }

            size_t tx = static_cast<size_t>(target_x);
            size_t ty = static_cast<size_t>(target_y);

            const Wall *wall = wall_store_.GetAt(tx, ty);
            if (wall) {
                if (wall->GetType() == WallType::Hard) {
                    break;
                } else {
                    wall_store_.RemoveAt(tx, ty);
                    presenter_.PresentWallDestroyed(tx, ty);
                    TrySpawnBonus(tx, ty);
                    smoke_store_.Add(Smoke(tx, ty, 1));
                    presenter_.PresentSmokePlaced(tx, ty);
                    CheckDamageTile(tx, ty);
                    break;
                }
            }

            smoke_store_.Add(Smoke(tx, ty, 1));
            presenter_.PresentSmokePlaced(tx, ty);
            CheckDamageTile(tx, ty);
        }
    }
}

void TickBombs::TrySpawnBonus(size_t x, size_t y) {
    const auto &chances = map_store_.GetBonusChances();
    std::vector<BonusType> available_types;

    if (chances.flame)      available_types.push_back(BonusType::FlameLength);
    if (chances.delay)      available_types.push_back(BonusType::BombCooldown);
    if (chances.health)     available_types.push_back(BonusType::Health);
    if (chances.frozen)     available_types.push_back(BonusType::Freeze);
    if (chances.levitation) available_types.push_back(BonusType::Levitation);

    if (available_types.empty()) return;

    if (std::rand() % 2 == 0) {
        BonusType picked = available_types[static_cast<size_t>(std::rand()) % available_types.size()];
        bonus_store_.Add(Bonus(x, y, picked));
        bonus_presenter_.PresentBonusSpawned(x, y);
    }
}