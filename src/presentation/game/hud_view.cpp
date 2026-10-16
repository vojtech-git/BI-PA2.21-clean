#include "hud_view.hpp"
#include <iomanip>
#include <sstream>

namespace HudLayout {
    constexpr int NAME_OFFSET  = 0;
    constexpr int NAME_WIDTH   = 10;
    constexpr int HP_OFFSET    = 12;
    constexpr int HP_WIDTH     = 7;
    constexpr int FLAME_OFFSET = 21;
    constexpr int FLAME_WIDTH  = 8;
    constexpr int CD_OFFSET    = 31;
    constexpr int CD_WIDTH     = 7;
    constexpr int BUFF_OFFSET  = 40;
    constexpr int BUFF_WIDTH   = 6;
}

HudView::~HudView() {
    if (window_) {
        delwin(window_);
        window_ = nullptr;
    }
}

void HudView::InitWindow(int y, int x, int width, int height) {
    if (window_) {
        delwin(window_);
    }
    y_ = y;
    x_ = x;
    width_ = width;
    height_ = height;
    window_ = newwin(height_, width_, y_, x_);
}

void HudView::Reset() {
    player_slots_.clear();
    next_slot_ = 0;
    if (window_) {
        werase(window_);
    }
}

void HudView::SetPosition(int y, int x) {
    y_ = y;
    x_ = x;
    if (window_) {
        mvwin(window_, y_, x_);
    }
}

void HudView::ClearField(int y, int x, int width) {
    if (!window_) return;
    std::string spaces(width, ' ');
    mvwaddnstr(window_, y, x, spaces.c_str(), width);
}

void HudView::AddPlayerSlot(int player_id, const std::string &name) {
    if (!window_) return;
    int slot = next_slot_++;
    player_slots_[player_id] = slot;
    int y = slot;

    ClearField(y, HudLayout::NAME_OFFSET, HudLayout::NAME_WIDTH);
    mvwaddnstr(window_, y, HudLayout::NAME_OFFSET, name.c_str(), HudLayout::NAME_WIDTH);
}

void HudView::UpdatePlayer(int player_id, int health, size_t explosion_size, float cd, bool frozen, bool levitating) {
    auto it = player_slots_.find(player_id);
    if (!window_ || it == player_slots_.end()) return;
    int y = it->second;

    // HP
    ClearField(y, HudLayout::HP_OFFSET, HudLayout::HP_WIDTH);
    std::string hp = "HP:" + std::to_string(health);
    mvwaddnstr(window_, y, HudLayout::HP_OFFSET, hp.c_str(), HudLayout::HP_WIDTH);

    // Flame length
    ClearField(y, HudLayout::FLAME_OFFSET, HudLayout::FLAME_WIDTH);
    std::string flame = "F:" + std::to_string(explosion_size);
    mvwaddnstr(window_, y, HudLayout::FLAME_OFFSET, flame.c_str(), HudLayout::FLAME_WIDTH);

    // Bomb cooldown
    ClearField(y, HudLayout::CD_OFFSET, HudLayout::CD_WIDTH);
    std::ostringstream ss;
    ss << "CD:" << std::fixed << std::setprecision(1) << cd;
    mvwaddnstr(window_, y, HudLayout::CD_OFFSET, ss.str().c_str(), HudLayout::CD_WIDTH);

    // Buffs
    ClearField(y, HudLayout::BUFF_OFFSET, HudLayout::BUFF_WIDTH);
    std::string buffs;
    if (frozen) buffs += "F ";
    if (levitating) buffs += "V ";
    if (buffs.empty()) buffs = "-";
    mvwaddnstr(window_, y, HudLayout::BUFF_OFFSET, buffs.c_str(), HudLayout::BUFF_WIDTH);
}

void HudView::StageRender() {
    if (window_) {
        wnoutrefresh(window_);
    }
}

void HudView::ClearWindow() {
    if (window_) {
        werase(window_);
        wnoutrefresh(window_);
        delwin(window_);
        window_ = nullptr;
    }
}

void HudView::UpdatePlayerHealth(int player_id, int health) {
    auto it = player_slots_.find(player_id);
    if (!window_ || it == player_slots_.end()) return;
    int y = it->second;

    ClearField(y, HudLayout::HP_OFFSET, HudLayout::HP_WIDTH);
    std::string hp = "HP:" + std::to_string(health);
    mvwaddnstr(window_, y, HudLayout::HP_OFFSET, hp.c_str(), HudLayout::HP_WIDTH);
}