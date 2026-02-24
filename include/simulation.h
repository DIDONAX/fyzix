#pragma once

#include "engine.h"
#include "renderer.h"
#include "types.h"

struct Simulation {
    Engine* engine_;
    Renderer* renderer_;

    Simulation(Engine& e, Renderer& r);

    void register_sys(Object& o, Force& f); 

    void start();
};
