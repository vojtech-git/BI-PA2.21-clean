#include "application/maps/navigate_to_map_select.hpp"

NavigateToMapSelect::NavigateToMapSelect(MapConfigurationRepository &repo, MapSelectPresenter &presenter)
    : repo_(repo), presenter_(presenter) {}

void NavigateToMapSelect::Execute() {
    auto maps = repo_.LoadAllMapNames();
    presenter_.PresentMapSelect(maps);
}