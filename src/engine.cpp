#include "engine.h"
#include <print>
#include <variant>

Engine::Engine(EulerSolver& solver) : solver_(&solver){};

void Engine::register_sys(Object& o, Force& f) {
    system_[&o].push_back(f);
}

const System& Engine::get_sys() const {
    return system_;
}

void Engine::step() {
    // std::println("applying forces...");
    for (auto& [o, fs] : system_) {
        for (Force& force : fs) {
            if (force.has_value()) {
                std::visit([&](auto& f) {
                        f.apply(*o);
                }, *force);
            }
        }
    }
    // std::println("solving ode...");
    for (auto& [o, _] : system_) {
            solver_->solve(o);
            // std::println("x = {}, y = {}", o->p_.x_, o->p_.y_);
    }
    // std::println("step complete");
}
