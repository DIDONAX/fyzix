#pragma once
#include "particle.h"
#include <cmath>

using particle = fyzix::particle;

namespace fyzix::engine {

    inline void integrate(particle& p, const float dt) {
        vec2 net_acc = p.forces_ * p.inv_mass_;
        p.position_ += p.velocity_ * dt + net_acc * dt * dt * 0.5;
        p.velocity_ = p.velocity_ * std::pow(p.damping_, dt) + net_acc * dt; 
    }

    inline void step(particle& p, const float dt) {
        float step = dt/5;
        for (int i = 0; i < 5; ++i) {
            // todo: apply forces
            integrate(p, step);
            p.clear_forces();
        }
    }

}
