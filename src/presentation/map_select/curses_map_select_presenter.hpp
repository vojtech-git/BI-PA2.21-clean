#pragma once
#include "presentation/view.hpp"
#include "presentation/app_state.hpp"
#include "map_select_state.hpp"
#include "application/maps/map_select_presenter.hpp"
#include <vector>
#include <string>
#include <optional>

class CursesMapSelectPresenter : public MapSelectPresenter {
public:
    CursesMapSelectPresenter(View &view, AppState &app_state);
    void PresentMapSelect(const std::vector<std::string> &maps) override;
    void PresentSelectedMap(const std::string &mapName) override;
    void ChangePage(int delta);
    std::optional<std::string> GetMapAtSlot(int slotIndex) const;

private:
    void Render();
    View &view_;
    AppState &app_state_;
    MapSelectState state_;
};