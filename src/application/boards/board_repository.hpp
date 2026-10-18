#pragma once

#include <optional>
#include "domain/boards/board.hpp"

class BoardRepository {
public:
    virtual ~BoardRepository() = default;

    virtual std::optional<Board> Get() const = 0;
    virtual void Save(const Board &board) = 0;
    virtual void Clear() = 0;
};