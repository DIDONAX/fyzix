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

    void register_sys(Mass& o,Constraint& c); 
    void register_sys(Mass& o, Force&); 
    const SystemF& get_sysf() const;
    const SystemC& get_sysc() const;
    void step(); 
};
