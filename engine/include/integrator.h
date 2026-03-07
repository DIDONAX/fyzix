#pragma once 
#include "particle.h"


namespace fyzix {

struct integrator {
    float dt_;
    float n_;

    integrator();
    integrator(const float dt, const float n);
    void solve(particle& p); 
};

}
