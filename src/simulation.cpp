#include "simulation.h"
#include <print>

Simulation::Simulation(Engine& e, Renderer& r) : engine_(&e), renderer_(&r) {}

void Simulation::register_sys(Object& o, Force& f) {
    engine_->register_sys(o, f);
}
void Simulation::start() {
    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case (SDL_EVENT_QUIT): 
                    std::println("Simulation Ended");
                    running = false;
                    break;
                default:
                    break;
            }
        }
        engine_->step();
        renderer_->render(engine_->get_sys());
    }
}
