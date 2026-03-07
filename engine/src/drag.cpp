#include "drag.h"

namespace fyzix {

drag::drag(const float k1, const float k2) : k1_(k1), k2_(k2) {}

void drag::apply(particle* p,float dt) {
    if (p->inv_mass_ == 0) return;

    vec2 force = p->velocity_;

    float coeff = force.magnitude();
    coeff =  k1_*coeff + k2_*coeff*coeff;

    force.normalize();
    force*= -coeff;
 
    p->apply_force(force);
}

}
