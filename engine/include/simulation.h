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

    template<typename T>
    void register_sys(RObject& o, T&& sys) {
        engine_->register_sys(*(o.obj_), std::forward<T>(sys));
        if (engine_->objs_.size() != scene_.size()) {
            scene_.push_back(&o);
        }
    }

    void start();
};
