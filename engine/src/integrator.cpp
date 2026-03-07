#include "integrator.h"

namespace fyzix {

integrator::integrator() : dt_(0.001), n_(1) {}
integrator::integrator(float dt, float n) : dt_(dt), n_(n) {}

// newton-Euler integration can be innacuarate in some cases
void integrator::solve(particle& p) {
    for (int i = 0; i < n_; ++i) {
        p.position_ += p.velocity_ * dt_ + p.acceleration_ * dt_ * dt_ * 0.5;

        // suitable for small set of particels 
        p.velocity_ += p.velocity_ * std::pow(p.damping_, dt_) + p.acceleration_ * dt_; 
    }
}

}
