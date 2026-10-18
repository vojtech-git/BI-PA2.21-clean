#pragma once

#include "application/maps/map_selection_repository.hpp"

class MemoryMapSelectionRepository : public MapSelectionRepository {
public:
    void SetSelectedMapName(const std::string &map_name) override {
        selected_map_name_ = map_name;
    }

    std::string GetSelectedMapName() const override {
        return selected_map_name_;
    }

private:
    std::string selected_map_name_{};
};