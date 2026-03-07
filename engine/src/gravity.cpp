#include "gravity.h"
namespace fyzix {

gravity::gravity(const vec2& g) : g_(g) {}

void gravity::apply(particle* p,float dt) {
    if (p->inv_mass_ == 0) return;
    p->apply_force(g_ * p->mass_);
}

}
