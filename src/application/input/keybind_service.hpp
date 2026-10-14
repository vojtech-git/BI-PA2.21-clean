#pragma once
#include <functional>

class KeybindService {
public:
    virtual ~KeybindService() = default;
    virtual void BindDynamicKey(int key, std::function<void()> action) = 0;
    virtual void ClearDynamicKeys() = 0;
};