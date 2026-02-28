#include "simulation.h"
#include "constants.h"
#include "engine.h"
#include "solver.h"
#include "types.h"
#include "utils.h"
#include <print>

Simulation::Simulation(Engine& e, Renderer& r, std::string t) : engine_(&e), renderer_(&r), title_(t) {}

void Simulation::start() {
    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: 
                    std::println("Simulation Ended");
                    running = false;
                    break;
                case SDL_EVENT_MOUSE_WHEEL:
                    if (event.wheel.y > 0) {
                        renderer_->scale_ *= 1.1f;
                    } else if (event.wheel.y < 0) {
                        renderer_->scale_ /= 1.1f;
                    }
                break;
                default:
                    break;
            }
        }

        engine_->step();

        renderer_->clear();
        for (const auto& o : scene_) {
            renderer_->draw(title_, 10, 10, 2);
            renderer_->draw_grid();

            for (const auto& c : engine_->systemc_.at(o->obj_)) {
                renderer_->draw(*o, c);
            }

            for (const auto& f : engine_->systemf_.at(o->obj_)) {
                renderer_->draw(*o, f);
            }
            renderer_->draw(*o);
        }
        renderer_->render();
    }
}
