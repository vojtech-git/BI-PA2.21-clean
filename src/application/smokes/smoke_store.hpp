#pragma once
#include "domain/smokes/smoke.hpp"
#include <vector>
#include <cstddef>

class SmokeStore {
public:
    SmokeStore() = default;
    ~SmokeStore() = default;

    const std::vector<Smoke>& GetAll() const {
        return smokes_;
    }

    std::vector<Smoke>& GetAllMutable() {
        return smokes_;
    }

    void Add(Smoke smoke) {
        smokes_.push_back(smoke);
    }

    void Remove(size_t index) {
        if (index < smokes_.size()) {
            smokes_.erase(smokes_.begin() + index);
        }
    }

    void Clear() {
        smokes_.clear();
    }

private:
    std::vector<Smoke> smokes_;
};