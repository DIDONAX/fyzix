#pragma once

#include "engine.h"
#include "object.h"
#include "renderer.h"
#include "types.h"

struct Simulation {
    Engine* engine_;
    Renderer* renderer_;
    std::vector<RObject*> scene_;
    std::string title_;

    Simulation(Engine& e, Renderer& r, std::string t);

    void register_sys(RObject& o, Force& f); 
    void register_sys(RObject& o, Constraint& c); 

    void start();
};
