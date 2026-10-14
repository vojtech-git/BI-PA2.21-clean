#pragma once
#include <string>
#include <vector>

struct PlayerControlSummary {
    std::string name;
    std::string moveKeys;
    char bombKey;
};

struct GameHudConfig {
    std::vector<PlayerControlSummary> controls;
};