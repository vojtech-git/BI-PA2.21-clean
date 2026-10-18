#pragma once

#include <string>
#include "application/maps/map_selection_repository.hpp"
#include "application/maps/map_select_presenter.hpp"

class SelectMap {
public:
    SelectMap(MapSelectionRepository &selection_repo, MapSelectPresenter &presenter);
    void Execute(const std::string &map_name);

private:
    MapSelectionRepository &selection_repo_;
    MapSelectPresenter &presenter_;
};