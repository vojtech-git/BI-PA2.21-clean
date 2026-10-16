#include "move_player.hpp"

MovePlayer::MovePlayer(
    PlayerStore &player_store,
    MapStore &map_store,
    WallStore &wall_store,
    BombStore &bomb_store,
    PlayerPresenter &presenter
)
    : player_store_(player_store),
      map_store_(map_store),
      wall_store_(wall_store),
      bomb_store_(bomb_store),
      presenter_(presenter) {}

void MovePlayer::Execute(int player_id, int dx, int dy) {
    Player *player = player_store_.GetById(player_id);
    if (!player || player->IsDead() || player->isFrozen()) {
        return;
    }

    size_t old_x = player->GetX();
    size_t old_y = player->GetY();

    long long target_x = static_cast<long long>(old_x) + dx;
    long long target_y = static_cast<long long>(old_y) + dy;

    Map map = map_store_.Get();
    if (target_x < 0 || target_x >= static_cast<long long>(map.GetWidth()) ||
        target_y < 0 || target_y >= static_cast<long long>(map.GetHeight())) {
        return;
    }

    size_t next_x = static_cast<size_t>(target_x);
    size_t next_y = static_cast<size_t>(target_y);

    if (IsTileBlocked(next_x, next_y, player->isLevitating())) {
        return;
    }

    player->Move(next_x, next_y);
    presenter_.PresentPlayerMoved(old_x, old_y, next_x, next_y);
}

bool MovePlayer::IsTileBlocked(size_t x, size_t y, bool is_levitating) const {
    for (const auto &wall : wall_store_.GetAll()) {
        if (wall.GetX() == x && wall.GetY() == y){
            if (wall.GetType() == WallType::Hard || !is_levitating) {
                return true;
            }
        }
    }

    for (const auto &bomb : bomb_store_.GetAll()) {
        if (bomb.GetX() == x && bomb.GetY() == y) {
            return true;
        }
    }

    return false;
}