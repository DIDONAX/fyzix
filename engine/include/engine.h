#pragma once

#include <vector>

#include "solver.h"
#include "types.h"

struct Engine {
    System system_;
    EulerSolver* solver_;

    Engine(EulerSolver& solver);

    void register_sys(Mass& o, Force& f); 
    const System& get_sys() const;
    void reset_a(Mass& o) const ; 
    void step(); 
};
