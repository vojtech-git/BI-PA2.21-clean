#include "curses_wrapper.hpp"
#include "presentation/app_state.hpp"
#include "presentation/view.hpp"
#include "presentation/event_router.hpp"
#include "presentation/game/hud_view.hpp"
#include "presentation/game/board_view.hpp"
#include "presentation/game/controls_view.hpp"
#include "presentation/main_menu/main_menu_presenter.hpp"
#include "presentation/leaderboard/curses_leaderboard_presenter.hpp"
#include "presentation/map_select/curses_map_select_presenter.hpp"
#include "presentation/game/curses_game_start_presenter.hpp"
#include "presentation/players/curses_player_presenter.hpp"
#include "integration/file_leaderboard_repository.hpp"
#include "integration/file_map_repository.hpp"
#include "application/maps/map_store.hpp"
#include "application/walls/wall_store.hpp"
#include "application/players/player_store.hpp"
#include "application/ghosts/ghost_store.hpp"
#include "application/doors/door_store.hpp"
#include "application/bombs/bomb_store.hpp"
#include "application/leaderboards/navigate_to_leaderboard.hpp"
#include "application/maps/navigate_to_map_select.hpp"
#include "application/maps/select_map.hpp"
#include "application/players/move_player.hpp"
#include "application/games/start_game.hpp"
#include <chrono>
#include <thread>

int main() {
    AppState app_state = AppState::MainMenu;
    View view;
    EventRouter router(app_state);

    // Dedicated game sub-views
    HudView hud_view;
    BoardView board_view;
    ControlsView controls_view;

    // Repositories & Stores
    FileLeaderboardRepository leaderboard_repo;
    FileMapRepository map_repo;
    MapStore map_store;
    WallStore wall_store;
    PlayerStore player_store;
    GhostStore ghost_store;
    DoorStore door_store;
    BombStore bomb_store;

    // Presenters
    MainMenuPresenter main_menu_presenter(view, app_state);
    CursesLeaderboardPresenter leaderboard_presenter(view, app_state);
    CursesMapSelectPresenter map_select_presenter(view, app_state);
    CursesGameStartPresenter start_game_presenter(view, app_state, hud_view, board_view, controls_view);
    CursesPlayerPresenter player_presenter(board_view);

    // Use cases
    NavigateToLeaderboard navigate_to_leaderboard(leaderboard_repo, leaderboard_presenter);
    NavigateToMapSelect navigate_to_map_select(map_repo, map_select_presenter);
    SelectMap select_map(map_store, map_select_presenter);
    MovePlayer move_player(player_store, map_store, wall_store, bomb_store, player_presenter);
    StartGame start_game(
        map_repo,
        map_store,
        wall_store,
        player_store,
        ghost_store,
        door_store,
        router,
        move_player,
        start_game_presenter
    );

    bool running = true;

    // Keybindings
    router.BindKey(AppState::MainMenu, 'p', [&]() { start_game.Execute(); });
    router.BindKey(AppState::MainMenu, 'l', [&]() { navigate_to_leaderboard.Execute(); });
    router.BindKey(AppState::MainMenu, 'm', [&]() { navigate_to_map_select.Execute(); });
    router.BindKey(AppState::MainMenu, 'q', [&]() { running = false; });

    router.BindKey(AppState::Leaderboard, KEY_LEFT, [&]() { leaderboard_presenter.ChangePage(-1); });
    router.BindKey(AppState::Leaderboard, KEY_RIGHT, [&]() { leaderboard_presenter.ChangePage(1); });
    router.BindKey(AppState::Leaderboard, 'q', [&]() { main_menu_presenter.PresentMainMenu(); });

    router.BindKey(AppState::MapSelect, KEY_LEFT, [&]() { map_select_presenter.ChangePage(-1); });
    router.BindKey(AppState::MapSelect, KEY_RIGHT, [&]() { map_select_presenter.ChangePage(1); });
    auto handle_slot_selection = [&](int slot) {
        if (auto map_name = map_select_presenter.GetMapAtSlot(slot)) {
            select_map.Execute(*map_name);
        }
    };
    router.BindKey(AppState::MapSelect, '1', [&]() { handle_slot_selection(0); });
    router.BindKey(AppState::MapSelect, '2', [&]() { handle_slot_selection(1); });
    router.BindKey(AppState::MapSelect, '3', [&]() { handle_slot_selection(2); });
    router.BindKey(AppState::MapSelect, '4', [&]() { handle_slot_selection(3); });
    router.BindKey(AppState::MapSelect, 'q', [&]() { main_menu_presenter.PresentMainMenu(); });

    router.BindKey(AppState::Game, 'q', [&]() {
    hud_view.ClearWindow();
    board_view.ClearWindow();
    controls_view.ClearWindow();
    main_menu_presenter.PresentMainMenu();
    });

    main_menu_presenter.PresentMainMenu();

    while (running) {
        int ch = view.GetInput();
        if (ch != -1 && ch != 0) {
            router.dispatchKey(app_state, ch);
        }

        if (app_state == AppState::Game) {
            hud_view.StageRender();
            board_view.StageRender();
            controls_view.StageRender();
            doupdate();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}