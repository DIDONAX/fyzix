#pragma once

#include "force_gen.h"
#include "particle.h"

namespace fyzix {

struct gravity : force_generator {
    vec2 g_;

    gravity(const vec2& g);
    void apply(particle* p, float dt); 
};

}
