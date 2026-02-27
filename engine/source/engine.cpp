#include "engine.h"
#include <print>
#include <variant>

Engine::Engine(EulerSolver& solver) : solver_(&solver){};

void Engine::register_sys(Mass& o, Force& f) {
    system_[&o].push_back(f);
}

const System& Engine::get_sys() const {
    return system_;
}

void Engine::step() {
    for (auto& [o, fs] : system_) {
        for (Force& force : fs) {
            if (force.has_value()) {
                std::visit([&](auto& f) {
                        f.apply(*o);
                }, *force);
            }
        }
    }
    for (auto& [o, _] : system_) {
            solver_->solve(o);
    }
}
