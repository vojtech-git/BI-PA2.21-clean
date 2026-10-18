#pragma once
#include "application/common/repository.hpp"
#include "domain/players/player.hpp"

class PlayerRepository : public virtual IRepository<Player, PlayerId> {};