#pragma once

#include "application/common/id_generator_service.hpp"

class SimpleIdGeneratorService : public IdGeneratorService {
public:
    SimpleIdGeneratorService() = default;

    void ResetAll() override {
        counters_.clear();
    }

protected:
    uint32_t GenerateNextValue(std::type_index type) override {
        return ++counters_[type];
    }

    void ResetValue(std::type_index type) override {
        counters_[type] = 0;
    }

private:
    std::unordered_map<std::type_index, uint32_t> counters_;
};