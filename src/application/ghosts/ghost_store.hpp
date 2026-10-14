#pragma once
#include "domain/ghosts/ghost.hpp"
#include <vector>

class GhostStore
{
public:
    GhostStore() = default;
    ~GhostStore() = default;

    const std::vector<Ghost>& GetAll() const { return ghosts_; }
    void Add(const Ghost &ghost) { ghosts_.push_back(ghost); }
    void Clear() { ghosts_.clear(); }

private:
    std::vector<Ghost> ghosts_;
};