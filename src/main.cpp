#include "curses_wrapper.hpp"
#include "presentation/app_state.hpp"
#include "presentation/view.hpp"
#include "presentation/event_router.hpp"
#include "presentation/game/game_board_buffer.hpp"
#include "presentation/main_menu/main_menu_presenter.hpp"
#include "presentation/leaderboard/curses_leaderboard_presenter.hpp"
#include "presentation/map_select/curses_map_select_presenter.hpp"
#include "presentation/game/curses_game_presenter.hpp"
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

int main()
{
    AppState app_state = AppState::MainMenu;
    View view;
    EventRouter router(app_state);
    GameBoardBuffer board_buffer;

    // Repositories
    FileLeaderboardRepository leaderboard_repo;
    FileMapRepository map_repo;

    // Stores
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
    CursesGamePresenter game_presenter(view, app_state, board_buffer, player_store);
    CursesPlayerPresenter player_presenter(board_buffer);

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
        game_presenter
    );

    bool running = true;

    // --- Main Menu Bindings ---
    router.BindKey(AppState::MainMenu, 'p', [&]() { start_game.Execute(); });
    router.BindKey(AppState::MainMenu, 'P', [&]() { start_game.Execute(); });
    router.BindKey(AppState::MainMenu, 'l', [&]() { navigate_to_leaderboard.Execute(); });
    router.BindKey(AppState::MainMenu, 'L', [&]() { navigate_to_leaderboard.Execute(); });
    router.BindKey(AppState::MainMenu, 'm', [&]() { navigate_to_map_select.Execute(); });
    router.BindKey(AppState::MainMenu, 'M', [&]() { navigate_to_map_select.Execute(); });
    router.BindKey(AppState::MainMenu, 'q', [&]() { running = false; });
    router.BindKey(AppState::MainMenu, 'Q', [&]() { running = false; });

    // --- Leaderboard Bindings ---
    router.BindKey(AppState::Leaderboard, KEY_LEFT, [&]() { leaderboard_presenter.ChangePage(-1); });
    router.BindKey(AppState::Leaderboard, KEY_RIGHT, [&]() { leaderboard_presenter.ChangePage(1); });
    router.BindKey(AppState::Leaderboard, 'q', [&]() { main_menu_presenter.PresentMainMenu(); });
    router.BindKey(AppState::Leaderboard, 'Q', [&]() { main_menu_presenter.PresentMainMenu(); });

    // --- Map Select Bindings ---
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
    router.BindKey(AppState::MapSelect, 'Q', [&]() { main_menu_presenter.PresentMainMenu(); });

    // --- In-Game Bindings ---
    router.BindKey(AppState::Game, 'q', [&]() { main_menu_presenter.PresentMainMenu(); });
    router.BindKey(AppState::Game, 'Q', [&]() { main_menu_presenter.PresentMainMenu(); });

    main_menu_presenter.PresentMainMenu();

    while (running)
    {
        int ch = view.GetInput();
        if (ch != -1 && ch != 0)
        {
            router.dispatchKey(app_state, ch);
        }

        if (app_state == AppState::Game)
        {
            game_presenter.Render();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}