#pragma once

#include "application/boards/board_repository.hpp"

class MemoryBoardRepository : public BoardRepository {
public:
    std::optional<Board> Get() const override {
        return board_;
    }

    void Save(const Board &board) override {
        board_ = board;
    }

    void Clear() override {
        board_ = std::nullopt;
    }

private:
    std::optional<Board> board_{std::nullopt};
};