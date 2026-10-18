#pragma once

#include "domain/common/entity_id.hpp"

enum class MoveDirection {
    Up,
    Down,
    Left,
    Right
};

class KeybindService {
public:
    virtual ~KeybindService() = default;
    virtual void BindPlayerMove(int key, PlayerId player_id, MoveDirection dir) = 0;
    virtual void BindPlayerBomb(int key, PlayerId player_id) = 0;
    virtual void ClearDynamicKeys() = 0;
};