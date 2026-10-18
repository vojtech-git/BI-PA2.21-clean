#include "application/maps/select_map.hpp"

SelectMap::SelectMap(MapSelectionRepository &selection_repo, MapSelectPresenter &presenter)
    : selection_repo_(selection_repo), presenter_(presenter) {}

void SelectMap::Execute(const std::string &map_name) {
    selection_repo_.SetSelectedMapName(map_name);
    presenter_.PresentSelectedMap(map_name);
}