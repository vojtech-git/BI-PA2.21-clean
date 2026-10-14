#pragma once
#include <string>
#include <vector>

struct MapSelectState
{
    int currentPage{0};
    int totalPages{1};
    std::string selectedMap{""};
    std::vector<std::string> maps;
};