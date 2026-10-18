#include "application/bombs/tick_bombs.hpp"

#include <vector>
#include "domain/bombs/explosion_service.hpp"
#include "domain/bonuses/bonus_spawner_service.hpp"
#include "domain/common/game_constants.hpp"

TickBombs::TickBombs(
    BombRepository &bomb_repo,
    BoardRepository &board_repo,
    WallRepository &wall_repo,
    PlayerRepository &player_repo,
    GhostRepository &ghost_repo,
    DoorRepository &door_repo,
    SmokeRepository &smoke_repo,
    BonusRepository &bonus_repo,
    IdGeneratorService &id_generator,
    BombPresenter &presenter,
    GameWinPresenter &win_presenter
) : bomb_repo_(bomb_repo),
    board_repo_(board_repo),
    wall_repo_(wall_repo),
    player_repo_(player_repo),
    ghost_repo_(ghost_repo),
    door_repo_(door_repo),
    smoke_repo_(smoke_repo),
    bonus_repo_(bonus_repo),
    id_generator_(id_generator),
    presenter_(presenter),
    win_presenter_(win_presenter) {}

void TickBombs::Execute(float dt) {
    auto board_opt = board_repo_.Get();
    if (!board_opt.has_value()) {
        return;
    }

    auto bombs = bomb_repo_.GetAll();
    if (bombs.empty()) {
        return;
    }

    std::vector<Bomb> exploding_bombs;

    for (auto &bomb : bombs) {
        bomb.UpdateDetonationTimer(dt);
        if (bomb.GetDetonationTimer() <= 0.0f) {
            exploding_bombs.push_back(bomb);
        } else {
            bomb_repo_.Save(bomb);
        }
    }

    for (const auto &bomb : exploding_bombs) {
        Explode(bomb, *board_opt);
    }
}

void TickBombs::Explode(const Bomb &bomb, const Board &board) {
    bomb_repo_.DeleteById(bomb.GetId());
    presenter_.PresentBombExploded(bomb.GetX(), bomb.GetY());

    ExplosionOutcome outcome = ExplosionDomainService::ProcessExplosion(
        bomb,
        board,
        wall_repo_.GetAll(),
        player_repo_.GetAll(),
        ghost_repo_.GetAll()
    );

    // 1. Destroy walls, check doors and spawn bonuses
    for (const auto &wall_pos : outcome.destroyed_wall_tiles) {
        wall_repo_.DeleteAt(wall_pos.x, wall_pos.y);
        presenter_.PresentWallDestroyed(wall_pos.x, wall_pos.y);
        CheckDoorReveal(wall_pos);
        TrySpawnBonus(wall_pos, board);
    }

    // 2. Spawn and present smoke
    for (const auto &smoke_pos : outcome.smoke_tiles) {
        SmokeId smoke_id = id_generator_.Next<SmokeId>();
        smoke_repo_.Save(Smoke(smoke_id, smoke_pos, 1));
        presenter_.PresentSmokePlaced(smoke_pos.x, smoke_pos.y);
    }

    // 3. Persist and present affected player damage
    for (const auto &player : outcome.affected_players) {
        player_repo_.Save(player);
        int player_id = static_cast<int>(player.GetId().GetValue());

        if (player.IsDead()) {
            presenter_.PresentPlayerDied(player_id, player.GetX(), player.GetY());
        } else {
            presenter_.PresentPlayerDamaged(player_id, player.GetHealth());
        }
    }

    // 4. Remove and present killed ghosts
    for (const auto &ghost_id : outcome.killed_ghost_ids) {
        auto ghost = ghost_repo_.GetById(ghost_id);
        if (ghost.has_value()) {
            ghost_repo_.DeleteById(ghost_id);
            presenter_.PresentGhostDied(ghost->GetX(), ghost->GetY());
        }
    }
}

void TickBombs::TrySpawnBonus(Position pos, const Board &board) {
    auto rolled_bonus = BonusSpawnerService::RollBonus(board);
    if (!rolled_bonus.has_value()) {
        return;
    }

    BonusId bonus_id = id_generator_.Next<BonusId>();
    bonus_repo_.Save(Bonus(bonus_id, pos, *rolled_bonus));
    presenter_.PresentBonusSpawned(pos.x, pos.y);
}

void TickBombs::CheckDoorReveal(Position pos) {
    auto door = door_repo_.Get();
    if (door.has_value() && !door->IsRevealed() && door->GetPosition() == pos) {
        door->Reveal();
        door_repo_.Save(*door);
        win_presenter_.PresentDoorRevealed(pos.x, pos.y);
    }
}