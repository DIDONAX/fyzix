#pragma once

#include "SDL3/SDL_render.h"
#include "vec2.h"
#include "SDL3/SDL_pixels.h"
#include "constants.h"
#include <cmath>
#include <string>
#include <vector>

struct Mass {
    float m_;
    vec2 p_;
    vec2 v_;
    vec2 a_;
    vec2 prev_;

    Mass(float m, const vec2& p, const vec2& v, const vec2& a)
        : m_(m), p_(p), v_(v), a_(a), prev_(p) {}
};

struct RObject {
    Mass* obj_;
    std::vector<int> indices_;
    std::vector<SDL_Vertex> verts_;
    std::vector<float> offsets_;
    std::string label_;
    SDL_FColor color_;

    //for now always a circle
    RObject(Mass& o, const SDL_FColor& c, float r, std::string l = "") : obj_(&o), label_(l), color_(c) {
        float theta = 0;
        float x = o.p_.x_;
        float y = o.p_.y_;

        verts_.push_back({{x, y}, c, {}});
        offsets_.push_back(0);
        offsets_.push_back(0);
        verts_.push_back({{x+r, y}, c, {}});
        offsets_.push_back(r);
        offsets_.push_back(0);
        for (int i = 0; i < 30; ++i) {
            theta+=2*pi/30;
            float x0 = std::cos(theta) * r;
            float y0 = std::sin(theta) * r;
            verts_.push_back({{x+x0, y-y0}, c, {}});
            offsets_.push_back(x0);
            offsets_.push_back(-y0);
            indices_.insert(indices_.end(), {0, static_cast<int>(verts_.size()-2), static_cast<int>(verts_.size()-1)});
        } 
    }
};
