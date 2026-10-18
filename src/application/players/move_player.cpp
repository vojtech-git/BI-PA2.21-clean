#include "application/players/move_player.hpp"
#include "domain/collision/collision_service.hpp"

MovePlayer::MovePlayer(
    PlayerRepository &player_repo,
    BoardRepository &board_repo,
    WallRepository &wall_repo,
    BombRepository &bomb_repo,
    BonusRepository &bonus_repo,
    PlayerPresenter &presenter
) : player_repo_(player_repo),
    board_repo_(board_repo),
    wall_repo_(wall_repo),
    bomb_repo_(bomb_repo),
    bonus_repo_(bonus_repo),
    presenter_(presenter) {}

void MovePlayer::Execute(PlayerId player_id, int dx, int dy) {
    auto player_opt = player_repo_.GetById(player_id);
    if (!player_opt.has_value()) {
        return;
    }

    Player player = *player_opt;
    if (player.IsDead() || player.IsFrozen()) {
        return;
    }

    auto board_opt = board_repo_.Get();
    if (!board_opt.has_value()) {
        return;
    }

    long long target_x = static_cast<long long>(player.GetX()) + dx;
    long long target_y = static_cast<long long>(player.GetY()) + dy;

    if (target_x < 0 || target_y < 0) {
        return;
    }

    Position target_pos{static_cast<uint32_t>(target_x), static_cast<uint32_t>(target_y)};

    if (CollisionService::IsTileBlockedForPlayer(
            target_pos,
            *board_opt,
            wall_repo_.GetAll(),
            bomb_repo_.GetAll(),
            player.IsLevitating()
        )) {
        return;
    }

    uint32_t old_x = player.GetX();
    uint32_t old_y = player.GetY();

    player.Move(target_pos);

    auto collected_bonus = bonus_repo_.RemoveAt(target_pos.x, target_pos.y);
    if (collected_bonus.has_value()) {
        player.ApplyBonus(collected_bonus->GetType());
        presenter_.PresentBonusCollected(target_pos.x, target_pos.y);
        presenter_.PresentPlayerStatsUpdated(
            player.GetId().GetValue(),
            player.GetHealth(),
            player.GetExplosionSize(),
            player.GetMaxBombCooldown(),
            player.IsFrozen(),
            player.IsLevitating()
        );
    }

    player_repo_.Save(player);
    presenter_.PresentPlayerMoved(old_x, old_y, target_pos.x, target_pos.y);
}