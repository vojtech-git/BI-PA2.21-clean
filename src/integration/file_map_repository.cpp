#include "file_map_repository.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>

std::vector<std::string> FileMapRepository::LoadAllMapNames() {
    std::vector<std::string> maps;
    const std::string mapDirectory = "maps";
    if (std::filesystem::exists(mapDirectory)) {
        for (const auto &entry : std::filesystem::directory_iterator(mapDirectory)) {
            if (entry.is_regular_file()) {
                maps.push_back(entry.path().filename().string());
            }
        }
    }
    return maps;
}

std::optional<MapDto> FileMapRepository::LoadMap(const std::string &mapName) {
    std::string path = "maps/" + mapName;
    if (path.find(".txt") == std::string::npos) {
        path += ".txt";
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        return std::nullopt;
    }

    MapDto dto;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        int val = 0;
        if (key == "flameChance")      { iss >> val; dto.bonusChances.flame = (val != 0); }
        else if (key == "frozenChance")     { iss >> val; dto.bonusChances.frozen = (val != 0); }
        else if (key == "levitationChance") { iss >> val; dto.bonusChances.levitation = (val != 0); }
        else if (key == "delayChance")      { iss >> val; dto.bonusChances.delay = (val != 0); }
        else if (key == "healthChance")     { iss >> val; dto.bonusChances.health = (val != 0); }
        else if (key == "map") {
            iss >> dto.height >> dto.width;
            break;
        }
    }

    if (dto.height == 0 || dto.width == 0) {
        return std::nullopt;
    }

    for (size_t y = 0; y < dto.height; ++y) {
        if (!std::getline(file, line)) break;

        for (size_t x = 0; x < dto.width && x < line.length(); ++x) {
            char cell = line[x];
            switch (cell) {
                case '#':
                    dto.walls.push_back({x, y, WallType::Hard});
                    break;
                case '=':
                    dto.walls.push_back({x, y, WallType::Soft});
                    break;
                case 'D':
                    dto.walls.push_back({x, y, WallType::Soft});
                    dto.doorPosition = {x, y};
                    dto.hasDoor = true;
                    break;
                case 'G':
                    dto.ghosts.push_back({x, y});
                    break;
                default:
                    break;
            }
        }
    }

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);

        PlayerConfigDto player;
        if (iss >> player.y >> player.x >> player.name
                >> player.upKey >> player.leftKey >> player.downKey >> player.rightKey >> player.bombKey) {
            dto.players.push_back(player);
        }
    }

    return dto;
}