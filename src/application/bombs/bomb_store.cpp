#include "bomb_store.hpp"

const std::vector<Bomb>& BombStore::GetAll() const {
    return bombs_;
}

std::vector<Bomb>& BombStore::GetAllMutable() {
    return bombs_;
}

void BombStore::Add(const Bomb &bomb) {
    bombs_.push_back(bomb);
}

void BombStore::Remove(size_t index) {
    if (index < bombs_.size()) {
        bombs_.erase(bombs_.begin() + index);
    }
}

void BombStore::Clear() {
    bombs_.clear();
}