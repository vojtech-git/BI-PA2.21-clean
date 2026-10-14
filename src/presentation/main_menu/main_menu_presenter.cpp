#include "main_menu_presenter.hpp"
#include <vector>

MainMenuPresenter::MainMenuPresenter(View &view, AppState &app_state)
    : view_(view), app_state_(app_state)
{
}

MainMenuPresenter::~MainMenuPresenter()
{
}

void MainMenuPresenter::PresentMainMenu()
{
    app_state_ = AppState::MainMenu;
    view_.ClearScreen();

    int centerX = view_.GetWidth() / 2;
    view_.DrawText(centerX, 2, "BOMBERMAN");

    const std::vector<std::string> options = {
        "(P)lay Game",
        "(L)eaderboard",
        "(M)ap selection",
        "(Q)uit"};

    int selectionArea = ((view_.GetHeight() - 5) / 4) + 1;
    for (size_t i = 0; i < options.size(); ++i)
    {
        int y_pos = (selectionArea * static_cast<int>(i)) + 5;
        view_.DrawText(centerX, y_pos, options[i]);
    }

    view_.Render();
}