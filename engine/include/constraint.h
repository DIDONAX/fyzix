#pragma once

#include "object.h"
#include <optional>

constexpr std::nullopt_t NullC = std::nullopt;

struct DistanceC {
    float dist_;
    Mass* p_;
    DistanceC(Mass& p, float dist);
    ~DistanceC();

    void apply(Mass& m); 
};

