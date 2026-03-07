#pragma once

#include "force_gen.h"
#include "particle.h"

namespace fyzix {

struct spring : force_generator {
    float l_;
    float k_;
    particle* other_;

    spring(particle* other, float k, float l);
    void apply(particle* p, float dt); 
};

}
