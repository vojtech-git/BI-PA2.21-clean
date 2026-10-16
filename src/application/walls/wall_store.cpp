#include "wall_store.hpp"

bool WallStore::RemoveAt(size_t x, size_t y) {
    for (auto it = walls_.begin(); it != walls_.end(); ++it) {
        if (it->GetX() == x && it->GetY() == y) {
            walls_.erase(it);
            return true;
        }
    }
    return false;
}

const Wall* WallStore::GetAt(size_t x, size_t y) const {
    for (const auto &w : walls_) {
        if (w.GetX() == x && w.GetY() == y) return &w;
    }
    return nullptr;
}