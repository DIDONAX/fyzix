#include "constants.h"
#include "engine.h"
#include "object.h"
#include "constraint.h"
#include "renderer.h"
#include "simulation.h"
#include "solver.h"
#include "types.h"
#include <print>

int main() {
    float dt = 0.008;
    int n = 1;
    int scale = 50;

    EulerSolver solver(dt, n); 
    Engine e(solver);
    Renderer r(scale);
    Simulation sim(e, r, "Constraints Test");

    Mass m1(1, {0, 5}, {5,0}, {0,0});
    Mass m2(2, {0, 0}, {0,0}, {0,0});
    Mass a(1, {0, 7}, {0,0}, {0,0});

    RObject anchor(a, kWhite, 10);
    RObject mass1(m1, kBlue, 10);
    RObject mass2(m2, kRed, 10);

    Constraint constraint_to_anchor = DistanceC(a, 5);
    Constraint constraint_to_mass = DistanceC(m1, 5);

    Force nonef = NullF;
    Force g = Gravity();
    Force s = SpringF(7, 1, m1);

    // register anchor
    sim.register_sys(anchor, nonef);
 
    //register mass1
    sim.register_sys(mass1, g);
    sim.register_sys(mass1, constraint_to_anchor);

    //register mass2
    sim.register_sys(mass2, g);
    sim.register_sys(mass2, s);


    sim.start();
 
    return 0;
}
