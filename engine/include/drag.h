#pragma once

#include "force_gen.h"
#include "particle.h"

namespace fyzix {

struct drag : force_generator {
    float k1_;
    float k2_;

    drag(const float k1, const float k2);
    void apply(particle* p, float dt); 
};

}
