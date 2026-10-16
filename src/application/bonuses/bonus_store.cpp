#include "bonus_store.hpp"

const std::vector<Bonus>& BonusStore::GetAll() const {
    return bonuses_;
}

std::vector<Bonus>& BonusStore::GetAllMutable() {
    return bonuses_;
}

void BonusStore::Add(const Bonus &bonus) {
    bonuses_.push_back(bonus);
}

bool BonusStore::RemoveAt(size_t x, size_t y, Bonus *removed_bonus) {
    for (auto it = bonuses_.begin(); it != bonuses_.end(); ++it) {
        if (it->GetX() == x && it->GetY() == y) {
            if (removed_bonus) {
                *removed_bonus = *it;
            }
            bonuses_.erase(it);
            return true;
        }
    }
    return false;
}

void BonusStore::Clear() {
    bonuses_.clear();
}