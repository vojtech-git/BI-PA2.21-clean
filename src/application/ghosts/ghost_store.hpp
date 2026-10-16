#pragma once
#include "domain/ghosts/ghost.hpp"
#include <vector>
#include <cstddef>

class GhostStore {
public:
    GhostStore() = default;
    ~GhostStore() = default;

    const std::vector<Ghost>& GetAll() const { return ghosts_; }
    std::vector<Ghost>& GetAllMutable() { return ghosts_; }
    void Add(const Ghost &ghost) { ghosts_.push_back(ghost); }
    void Clear() { ghosts_.clear(); }

    bool RemoveAt(size_t x, size_t y) {
        for (auto it = ghosts_.begin(); it != ghosts_.end(); ++it) {
            if (it->GetX() == x && it->GetY() == y) {
                ghosts_.erase(it);
                return true;
            }
        }
        return false;
    }

private:
    std::vector<Ghost> ghosts_;
};