#include "engine.h"
#include "constraint.h"
#include <print>

Engine::Engine(EulerSolver& solver) : solver_(&solver){};

void Engine::register_sys(Mass& o, Constraint& c) {
    bool not_registered = !systemf_.contains(&o) && !systemc_.contains(&o);
 
    systemc_[&o].push_back(c);

    if (not_registered) {
        objs_.push_back(&o);
    }
}
void Engine::register_sys(Mass& o, Force& f) {
    bool not_registered = !systemf_.contains(&o) && !systemc_.contains(&o);
 
    systemf_[&o].push_back(f);

    if (not_registered) {
        objs_.push_back(&o);
    }
}

const SystemF& Engine::get_sysf() const {
    return systemf_;
}

const SystemC& Engine::get_sysc() const {
    return systemc_;
}

void Engine::step() {
    for (auto& o : objs_) {
        for (Force& force : systemf_[o]) {
            if (force.has_value()) {
                std::visit([&](auto& f) {
                        f.apply(*o);
                }, *force);
            }
        }
        o->prev_ = o->p_;

        solver_->solve(o);

        for (Constraint& constraint : systemc_[o]) {
            if (constraint.has_value()) {
                std::visit([&](auto& c) {
                        c.apply(*o);
                }, *constraint);
            }
        }

        o->v_.x_= (o->p_.x_ - o->prev_.x_)/solver_->dt_;
        o->v_.y_= (o->p_.y_ - o->prev_.y_)/solver_->dt_;
    }
}
