#pragma once
#include "presentation/view.hpp"
#include "presentation/app_state.hpp"

class MainMenuPresenter
{
private:
    View &view_;
    AppState &app_state_;

public:
    MainMenuPresenter(View &view, AppState &app_state);
    ~MainMenuPresenter();
    void PresentMainMenu();
};