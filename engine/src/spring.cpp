#include "spring.h"

namespace fyzix {

spring::spring(particle* other, float k, float l) : l_(l), k_(k), other_(other) {} 

void spring::apply(particle* p,float dt) {
    vec2 force = p->position_;
    force-= other_->position_;

    float magnitude = force.magnitude();

    magnitude = std::abs(magnitude - l_);
    magnitude *= k_;

    force.normalize();
    force*= -magnitude;
    p->apply_force(force);
}

}
