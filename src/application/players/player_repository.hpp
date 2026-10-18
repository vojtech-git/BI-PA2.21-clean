#pragma once
#include "application/common/repository.hpp"
#include "domain/players/player.hpp"

class PlayerRepository : public IRepository<Player, PlayerId> {};