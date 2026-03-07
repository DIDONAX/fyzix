#pragma once

#include "particle.h"

namespace fyzix {

struct force_generator {
    virtual void apply(particle* p, float dt) = 0; 
};

}
