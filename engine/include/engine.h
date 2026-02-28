#pragma once

#include <vector>

#include "constraint.h"
#include "solver.h"
#include "types.h"

struct Engine {
    SystemF systemf_;
    SystemC systemc_;
    EulerSolver* solver_;
    std::vector<Mass*> objs_;

    Engine(EulerSolver& solver);

    template<typename T>
    void register_sys(Mass& o, T&& sys) {
        using U = std::decay_t<T>;

        bool not_registered = !systemf_.contains(&o) && !systemc_.contains(&o);

        if constexpr (std::is_same_v<U, Force>) {
            systemf_[&o].push_back(std::forward<T>(sys));
        }
        else if constexpr (std::is_same_v<U, Constraint>) {
            systemc_[&o].push_back(std::forward<T>(sys));
        }

        if (not_registered) {
            objs_.push_back(&o);
            o.prev_.x_ = o.p_.x_ - o.v_.x_ * solver_->dt_;
            o.prev_.y_ = o.p_.y_ - o.v_.y_ * solver_->dt_;
        }
    }

    const SystemF& get_sysf() const;
    const SystemC& get_sysc() const;
    void step(); 
};
