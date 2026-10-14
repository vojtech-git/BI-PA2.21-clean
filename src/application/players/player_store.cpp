#include "player_store.hpp"

const std::vector<Player>& PlayerStore::GetAll() const {
    return players_;
}

std::vector<Player>& PlayerStore::GetAllMutable() {
    return players_;
}

Player* PlayerStore::GetById(int id) {
    if (id < 0 || static_cast<size_t>(id) >= players_.size()) {
        return nullptr;
    }
    return &players_[static_cast<size_t>(id)];
}

void PlayerStore::Add(const Player &player) {
    players_.push_back(player);
}

void PlayerStore::Clear() {
    players_.clear();
}