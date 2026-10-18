#pragma once

#include "application/maps/map_configuration_repository.hpp"
#include "application/maps/map_select_presenter.hpp"

class NavigateToMapSelect {
public:
    NavigateToMapSelect(MapConfigurationRepository &repo, MapSelectPresenter &presenter);
    void Execute();

private:
    MapConfigurationRepository &repo_;
    MapSelectPresenter &presenter_;
};