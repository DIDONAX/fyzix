#include "engine.h"
#include "renderer.h"
#include "simulation.h"
#include "solver.h"

int main() {
    float dt = 0.01;
    float n = 1;

    EulerSolver solver(dt, n); 
    Engine e(solver);
    Renderer r;

    //scaled down values (G = 1)
    Object sun     {5000.0f, {0.0f, 0.0f},   {0.0f, 0.0f},  {0.0f, 0.0f}};
    Object mercury {0.16f,   {60.0f, 0.0f},  {0.0f, 9.13f}, {0.0f, 0.0f}};
    Object venus   {2.45f,   {110.0f, 0.0f}, {0.0f, 6.74f}, {0.0f, 0.0f}};
    Object earth   {3.0f,    {170.0f, 0.0f}, {0.0f, 5.42f}, {0.0f, 0.0f}};
    Object mars    {0.32f,   {240.0f, 0.0f}, {0.0f, 4.56f}, {0.0f, 0.0f}}; 
    Object jupiter {318.0f,  {400.0f, 0.0f}, {0.0f, 3.53f}, {0.0f, 0.0f}};

    std::vector<Object*> bodies = {
        &sun, &mercury, &venus, &earth, &mars, 
        &jupiter
    };

    Simulation sim(e, r);
    Force none = NullF;
    for (Object* obj : bodies) {
        if (obj == &sun) {
            sim.register_sys(*obj, none);
            continue;
        } 
        for (Object* other : bodies) {
            Force g = GravF(*other);
            if (obj != other) {
                sim.register_sys(*obj, g);
            }
        }
    }
    sim.start();
    return 0;
}
