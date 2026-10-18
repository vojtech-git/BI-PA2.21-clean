#pragma once
#include "integration/memory_repository.hpp"
#include "application/players/player_repository.hpp"

class MemoryPlayerRepository 
    : public InMemoryRepository<Player, PlayerId>,
      public PlayerRepository {};