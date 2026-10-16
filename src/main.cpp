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
#include "presentation/bombs/curses_bomb_presenter.hpp"
#include "integration/file_leaderboard_repository.hpp"
#include "integration/file_map_repository.hpp"
#include "application/maps/map_store.hpp"
#include "application/walls/wall_store.hpp"
#include "application/players/player_store.hpp"
#include "application/ghosts/ghost_store.hpp"
#include "application/doors/door_store.hpp"
#include "application/bombs/bomb_store.hpp"
#include "application/smokes/smoke_store.hpp"
#include "application/leaderboards/navigate_to_leaderboard.hpp"
#include "application/maps/navigate_to_map_select.hpp"
#include "application/maps/select_map.hpp"
#include "application/players/move_player.hpp"
#include "application/players/place_bomb.hpp"
#include "application/bombs/tick_bombs.hpp"
#include "application/smokes/tick_smokes.hpp"
#include "application/games/start_game.hpp"
#include "application/players/tick_players.hpp"
#include "presentation/bonuses/curses_bonus_presenter.hpp"
#include "application/bonuses/bonus_store.hpp"
#include "application/bonuses/collect_bonuses.hpp"
#include "presentation/ghosts/curses_ghost_presenter.hpp"
#include "application/ghosts/move_ghosts.hpp"
#include "presentation/ghosts/curses_ghost_collision_presenter.hpp"
#include "application/ghosts/check_ghost_collision.hpp"
#include <chrono>
#include <thread>

int main() {
    AppState app_state = AppState::MainMenu;
    View view;
    EventRouter router(app_state);

    // Game views
    HudView hud_view;
    BoardView board_view;
    ControlsView controls_view;

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
    SmokeStore smoke_store;
    BonusStore bonus_store;

    // Presenters
    MainMenuPresenter main_menu_presenter(view, app_state);
    CursesLeaderboardPresenter leaderboard_presenter(view, app_state);
    CursesMapSelectPresenter map_select_presenter(view, app_state);
    CursesGameStartPresenter start_game_presenter(view, app_state, hud_view, board_view, controls_view);
    CursesPlayerPresenter player_presenter(board_view);
    CursesBombPresenter bomb_presenter(board_view, hud_view);
    CursesBonusPresenter bonus_presenter(board_view, hud_view);
    CursesGhostPresenter ghost_presenter(board_view);
    CursesGhostCollisionPresenter ghost_collision_presenter(board_view, hud_view);

    // Use cases
    NavigateToLeaderboard navigate_to_leaderboard(leaderboard_repo, leaderboard_presenter);
    NavigateToMapSelect navigate_to_map_select(map_repo, map_select_presenter);
    SelectMap select_map(map_store, map_select_presenter);
    CollectBonuses collect_bonuses(player_store, bonus_store, bonus_presenter);
    MovePlayer move_player(player_store, map_store, wall_store, bomb_store, collect_bonuses, player_presenter);
    PlaceBomb place_bomb(player_store, bomb_store, bomb_presenter);
    TickBombs tick_bombs(
        bomb_store,
        map_store,
        wall_store,
        player_store,
        ghost_store,
        smoke_store,
        bonus_store,
        bomb_presenter,
        bonus_presenter
    );    
    TickSmokes tick_smokes(smoke_store, bomb_presenter);
    TickPlayers tick_players(player_store);
    MoveGhosts move_ghosts(ghost_store, map_store, wall_store, bomb_store, ghost_presenter);
    CheckGhostCollision check_ghost_collision(player_store, ghost_store, ghost_collision_presenter);


    StartGame start_game(
        map_repo,
        map_store,
        wall_store,
        player_store,
        ghost_store,
        door_store,
        router,
        move_player,
        place_bomb,
        start_game_presenter
    );

    bool running = true;

    // Register Tick Hooks
    router.RegisterTick(AppState::Game, [&](float dt) {
        tick_players.Execute(dt);
        tick_bombs.Execute(dt);
        tick_smokes.Execute(dt);
        move_ghosts.Execute(dt);
        check_ghost_collision.Execute();
    });

    // --- Main Menu Bindings ---
    router.BindKey(AppState::MainMenu, 'p', [&]() { start_game.Execute(); });
    router.BindKey(AppState::MainMenu, 'l', [&]() { navigate_to_leaderboard.Execute(); });
    router.BindKey(AppState::MainMenu, 'm', [&]() { navigate_to_map_select.Execute(); });
    router.BindKey(AppState::MainMenu, 'q', [&]() { running = false; });

    // --- Leaderboard Bindings ---
    router.BindKey(AppState::Leaderboard, KEY_LEFT, [&]() { leaderboard_presenter.ChangePage(-1); });
    router.BindKey(AppState::Leaderboard, KEY_RIGHT, [&]() { leaderboard_presenter.ChangePage(1); });
    router.BindKey(AppState::Leaderboard, 'q', [&]() { main_menu_presenter.PresentMainMenu(); });

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

    // --- In-Game Bindings ---
    router.BindKey(AppState::Game, 'q', [&]() {
        hud_view.ClearWindow();
        board_view.ClearWindow();
        controls_view.ClearWindow();
        main_menu_presenter.PresentMainMenu();
    });

    main_menu_presenter.PresentMainMenu();

    auto last_time = std::chrono::steady_clock::now();

    while (running) {
        auto current_time = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(current_time - last_time).count();
        last_time = current_time;

        int ch = view.GetInput();
        if (ch != -1 && ch != 0) {
            router.dispatchKey(app_state, ch);
        }

        router.DispatchTick(app_state, dt);

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