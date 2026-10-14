#include "curses_game_presenter.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>

CursesGamePresenter::CursesGamePresenter(
    View &view,
    AppState &app_state,
    GameBoardBuffer &buffer,
    const PlayerStore &player_store
)
    : view_(view),
      app_state_(app_state),
      buffer_(buffer),
      player_store_(player_store) {}

void CursesGamePresenter::SetHudConfig(const GameHudConfig &config) {
    hud_config_ = config;
}

void CursesGamePresenter::PresentGame(
    const Map &map,
    const std::vector<Wall> &walls,
    const std::vector<Player> &players,
    const std::vector<Ghost> &ghosts,
    const std::optional<Door> &door
) {
    app_state_ = AppState::Game;
    buffer_.Resize(map.GetWidth(), map.GetHeight());
    buffer_.Clear();

    if (door.has_value() && door->IsRevealed()) {
        buffer_.AddEntity(door->GetX(), door->GetY(), EntityVisualLayer::Door);
    }

    for (const auto &w : walls) {
        auto layer = (w.GetType() == WallType::Hard) ? EntityVisualLayer::HardWall : EntityVisualLayer::SoftWall;
        buffer_.AddEntity(w.GetX(), w.GetY(), layer);
    }

    for (const auto &g : ghosts) {
        buffer_.AddEntity(g.GetX(), g.GetY(), EntityVisualLayer::Ghost);
    }

    for (const auto &p : players) {
        buffer_.AddEntity(p.GetX(), p.GetY(), EntityVisualLayer::Player);
    }

    Render();
}

void CursesGamePresenter::Render() {
    view_.ClearScreen();

    size_t width = buffer_.GetWidth();
    size_t height = buffer_.GetHeight();

    int startY = std::max(2, (view_.GetHeight() - static_cast<int>(height)) / 2);

    RenderHudTop(startY - 2);

    for (size_t y = 0; y < height; ++y) {
        std::string row(width, ' ');
        for (size_t x = 0; x < width; ++x) {
            row[x] = buffer_.GetTopChar(x, y);
        }
        view_.DrawText(view_.GetWidth() / 2, startY + static_cast<int>(y), row);
    }

    RenderControlsBottom(startY + static_cast<int>(height) + 1);

    view_.Render();
}

void CursesGamePresenter::RenderHudTop(int startY) {
    if (startY < 1) startY = 1;

    std::string hudLine;
    for (const auto &player : player_store_.GetAll()) {
        std::string buffs;
        if (player.isFrozen()) buffs += "F ";
        if (player.isLevitating()) buffs += "V ";
        if (buffs.empty()) buffs = "-";

        std::ostringstream cdStream;
        cdStream << std::fixed << std::setprecision(1) << player.GetBombCooldown();

        std::string item = player.GetName() + " [HP:" + std::to_string(player.GetHealth())
                         + " Flame:" + std::to_string(player.GetExplosionSize())
                         + " CD:" + cdStream.str() + "s"
                         + " Buffs:" + buffs + "]  ";
        hudLine += item;
    }

    view_.DrawText(view_.GetWidth() / 2, startY, hudLine);
}

void CursesGamePresenter::RenderControlsBottom(int startY) {
    int y = startY;

    for (const auto &ctrl : hud_config_.controls) {
        std::string text = ctrl.name + ": Move [" + ctrl.moveKeys + "] | Bomb [" + ctrl.bombKey + "]";
        view_.DrawText(view_.GetWidth() / 2, y++, text);
    }

    view_.DrawText(view_.GetWidth() / 2, y, "[Q: Back to Menu]");
}