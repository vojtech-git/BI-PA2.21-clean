#pragma once
#include "domain/players/player.hpp"
#include <vector>
#include <optional>

class PlayerStore {
public:
    PlayerStore() = default;
    ~PlayerStore() = default;

    const std::vector<Player>& GetAll() const;
    std::vector<Player>& GetAllMutable();
    Player* GetById(int id);

    void Add(const Player &player);
    void Clear();

private:
    std::vector<Player> players_;
};