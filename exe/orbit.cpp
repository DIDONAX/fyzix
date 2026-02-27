#include "constants.h"
#include "engine.h"
#include "object.h"
#include "renderer.h"
#include "simulation.h"
#include "solver.h"

int main() {
    //smaller step size = more accurate simulation
    float dt = 0.0009;
    int n = 1;
    int scale = 300;

    EulerSolver solver(dt, n); 
    Engine e(solver);
    Renderer r(scale);

    Mass sun     {1.0f, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}};
    Mass mercury {0.0000033f, {0.39f, 0.0f}, {0.0f, 1.60f}, {0.0f, 0.0f}};
    Mass venus   {0.0000245f, {0.72f, 0.0f}, {0.0f, 1.18f}, {0.0f, 0.0f}};
    Mass earth   {0.00003f, {1.0f, 0.0f}, {0.0f, 1.00f}, {0.0f, 0.0f}};
    Mass mars    {0.0000032f, {1.52f, 0.0f}, {0.0f, 0.81f}, {0.0f, 0.0f}};
    Mass jupiter {0.000954f, {5.2f, 0.0f}, {0.0f, 0.44f}, {0.0f, 0.0f}};

    // radiuses not accuarate
    std::vector<RObject> bodies = {
        RObject(sun, kRed, 30.0, "sun"),
        RObject(mercury, kGray, 8.0, "mercury"),
        RObject(venus, kYellow, 11.0, "venus"),
        RObject(earth, kBlue, 12.0, "earth"),
        RObject(mars, kOrange, 10.0, "mars"),
        RObject(jupiter, kBrown, 25.0, "jupiter")
    };


    Simulation sim(e, r, "Solar System Demo");
    for (RObject& ro : bodies) {
        if (ro.obj_ == &sun) {
            sim.register_sys(ro, NullF);
            continue;
        }
        for (RObject& other : bodies) {
            if (other.obj_ != ro.obj_) {
                Force g = GravF(*other.obj_);
                sim.register_sys(ro, g);
            }
        }
    }

    sim.start();
    return 0;
}
