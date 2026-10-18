#include "curses_wrapper.hpp"
#include "presentation/app_state.hpp"
#include "presentation/view.hpp"
#include "presentation/event_router.hpp"

// Views
#include "presentation/game/hud_view.hpp"
#include "presentation/game/board_view.hpp"
#include "presentation/game/controls_view.hpp"

// Presenters
#include "presentation/main_menu/main_menu_presenter.hpp"
#include "presentation/leaderboard/curses_leaderboard_presenter.hpp"
#include "presentation/map_select/curses_map_select_presenter.hpp"
#include "presentation/game/curses_game_start_presenter.hpp"
#include "presentation/players/curses_player_presenter.hpp"
#include "presentation/bombs/curses_bomb_presenter.hpp"
#include "presentation/ghosts/curses_ghost_presenter.hpp"
#include "presentation/ghosts/curses_ghost_collision_presenter.hpp"
#include "presentation/doors/curses_game_win_presenter.hpp"

// Repositories & Services
#include "integration/file_leaderboard_repository.hpp"
#include "integration/file_map_repository.hpp"
#include "integration/simple_id_generator_service.hpp"
#include "integration/memory_board_repository.hpp"
#include "integration/memory_map_selection_repository.hpp"
#include "integration/memory_player_repository.hpp"
#include "integration/memory_ghost_repository.hpp"
#include "integration/memory_wall_repository.hpp"
#include "integration/memory_bomb_repository.hpp"
#include "integration/memory_smoke_repository.hpp"
#include "integration/memory_bonus_repository.hpp"
#include "integration/memory_door_repository.hpp"

// Use cases
#include "application/leaderboards/navigate_to_leaderboard.hpp"
#include "application/maps/navigate_to_map_select.hpp"
#include "application/maps/select_map.hpp"
#include "application/players/move_player.hpp"
#include "application/players/place_bomb.hpp"
#include "application/players/tick_players.hpp"
#include "application/bombs/tick_bombs.hpp"
#include "application/smokes/tick_smokes.hpp"
#include "application/ghosts/move_ghosts.hpp"
#include "application/ghosts/check_ghost_collision.hpp"
#include "application/doors/check_win_condition.hpp"
#include "application/games/start_game.hpp"

#include <chrono>
#include <thread>

int main() {
    AppState app_state = AppState::MainMenu;
    View view;

    // 1. Views
    HudView hud_view;
    BoardView board_view;
    ControlsView controls_view;

    // 2. Repositories & Services
    FileLeaderboardRepository leaderboard_repo;
    FileMapRepository map_config_repo;
    SimpleIdGeneratorService id_generator;

    MemoryMapSelectionRepository map_selection_repo;
    MemoryBoardRepository board_repo;
    MemoryPlayerRepository player_repo;
    MemoryGhostRepository ghost_repo;
    MemoryWallRepository wall_repo;
    MemoryBombRepository bomb_repo;
    MemorySmokeRepository smoke_repo;
    MemoryBonusRepository bonus_repo;
    MemoryDoorRepository door_repo;

    // 3. Presenters
    MainMenuPresenter main_menu_presenter(view, app_state);
    CursesLeaderboardPresenter leaderboard_presenter(view, app_state);
    CursesMapSelectPresenter map_select_presenter(view, app_state);
    CursesGameStartPresenter start_game_presenter(view, app_state, hud_view, board_view, controls_view);
    CursesPlayerPresenter player_presenter(board_view, hud_view);
    CursesBombPresenter bomb_presenter(board_view, hud_view);
    CursesGhostPresenter ghost_presenter(board_view);
    CursesGhostCollisionPresenter ghost_collision_presenter(board_view, hud_view);
    CursesGameWinPresenter win_presenter(view, app_state, board_view, hud_view, controls_view);

    // 4. Player Use Cases (instantiated first for Router)
    MovePlayer move_player(player_repo, board_repo, wall_repo, bomb_repo, bonus_repo, player_presenter);
    PlaceBomb place_bomb(player_repo, bomb_repo, id_generator, bomb_presenter);

    // 5. Event Router
    EventRouter router(app_state, move_player, place_bomb);

    // 6. Navigation & Game Use Cases
    NavigateToLeaderboard navigate_to_leaderboard(leaderboard_repo, leaderboard_presenter);
    NavigateToMapSelect navigate_to_map_select(map_config_repo, map_select_presenter);
    SelectMap select_map(map_selection_repo, map_select_presenter);

    TickPlayers tick_players(player_repo);
    TickBombs tick_bombs(
        bomb_repo, board_repo, wall_repo, player_repo, ghost_repo,
        door_repo, smoke_repo, bonus_repo, id_generator, bomb_presenter, win_presenter
    );
    TickSmokes tick_smokes(smoke_repo, bomb_presenter);
    MoveGhosts move_ghosts(ghost_repo, board_repo, wall_repo, bomb_repo, ghost_presenter);
    CheckGhostCollision check_ghost_collision(player_repo, ghost_repo, ghost_collision_presenter);
    CheckWinCondition check_win_condition(player_repo, door_repo, board_repo, map_selection_repo, leaderboard_repo, win_presenter);

    StartGame start_game(
        map_config_repo,
        map_selection_repo,
        board_repo,
        wall_repo,
        player_repo,
        ghost_repo,
        door_repo,
        id_generator,
        router,
        start_game_presenter
    );

    bool running = true;

    // 7. Register Tick Hooks
    router.RegisterTick(AppState::Game, [&](float dt) {
        auto board = board_repo.Get();
        if (board && !board->IsGameOver()) {
            board->UpdateTimer(dt);
            board_repo.Save(*board);
        }

        tick_players.Execute(dt);
        tick_bombs.Execute(dt);
        tick_smokes.Execute(dt);
        move_ghosts.Execute(dt);
        check_ghost_collision.Execute();
        check_win_condition.Execute();
    });

    // 8. Key Bindings
    // --- Main Menu ---
    router.BindKey(AppState::MainMenu, 'p', [&]() { start_game.Execute(); });
    router.BindKey(AppState::MainMenu, 'l', [&]() { navigate_to_leaderboard.Execute(); });
    router.BindKey(AppState::MainMenu, 'm', [&]() { navigate_to_map_select.Execute(); });
    router.BindKey(AppState::MainMenu, 'q', [&]() { running = false; });

    // --- Leaderboard ---
    router.BindKey(AppState::Leaderboard, KEY_LEFT, [&]() { leaderboard_presenter.ChangePage(-1); });
    router.BindKey(AppState::Leaderboard, KEY_RIGHT, [&]() { leaderboard_presenter.ChangePage(1); });
    router.BindKey(AppState::Leaderboard, 'q', [&]() { main_menu_presenter.PresentMainMenu(); });

    // --- Map Select ---
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

    // --- In-Game ---
    router.BindKey(AppState::Game, 'q', [&]() {
        hud_view.ClearWindow();
        board_view.ClearWindow();
        controls_view.ClearWindow();
        main_menu_presenter.PresentMainMenu();
    });

    // 9. Initial Render & Event Loop
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