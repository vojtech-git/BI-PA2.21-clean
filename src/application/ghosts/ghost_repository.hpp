#pragma once
#include "application/common/repository.hpp"
#include "domain/ghosts/ghost.hpp"

class GhostRepository : public virtual IRepository<Ghost, GhostId> {};