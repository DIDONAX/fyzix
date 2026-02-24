#pragma once

#include <unordered_map>
#include <variant>
#include <vector>

#include "forces.h"
#include "object.h"
#include "solver.h"
#include "types.h"

struct Engine {
    std::unordered_map<Object*, Forces> system_;
    EulerSolver* solver_;

    Engine(EulerSolver& solver);

    void register_sys(Object& o, Force& f); 
    const System& get_sys() const;
    void reset_a(Object& o) const ; 
    void step(); 
};
