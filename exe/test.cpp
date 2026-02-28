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
    float dt = 0.008f;
    int n = 1;
    int scale = 50;

    EulerSolver solver(dt, n); 
    Engine e(solver);
    Renderer r(scale);
    Simulation sim(e, r, "Double Pendulum Demo");

    // create masses
    Mass anchor_mass(1, {0, 5}, {0,0}, {0,0});
    Mass m1(1, {0, 3}, {4,0}, {0,0});
    Mass m2(1, {0, 1}, {-3,0}, {0,0});

    // wrap in RObjects
    RObject anchor(anchor_mass, kWhite, 10);
    RObject mass1(m1, kBlue, 10);
    RObject mass2(m2, kRed, 10);

    // forces
    Force nonef = NullF;
    Force g = Gravity();

    // constraints
    Constraint c1 = DistanceC(anchor_mass, 4); // anchor <- mass1
    Constraint c2 = DistanceC(m1, 5); // mass1 <- mass2

    // register systems
    sim.register_sys(anchor, nonef);

    sim.register_sys(mass1, g);
    sim.register_sys(mass1, c1);

    sim.register_sys(mass2, g);
    sim.register_sys(mass2, c2);

    sim.start();
    return 0;
}
