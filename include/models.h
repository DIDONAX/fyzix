#pragma once

#include <cmath>
#include <vector>

#include "SDL3/SDL_render.h"

#include "constants.h"

struct ModelInfo {
    std::vector<SDL_Vertex> vertices_;
    SDL_Texture* texture_{nullptr};
    std::vector<int> indices_;
};

struct Circle {
    ModelInfo m_;
    Circle(float x = center_x, float y = center_y, float r = 50, const SDL_FColor& color = kRed, const int res = 30) {
        float theta = 0;
        m_.vertices_.push_back({{x, y}, color, {}});
        m_.vertices_.push_back({{x+r, y}, color, {}});
        for (int i = 0; i < res-1; ++i) {
            theta+=2*pi/res;
            float x0 = std::cos(theta) * r;
            float y0 = std::sin(theta) * r;
            m_.vertices_.push_back({{x+x0, y-y0}, color, {}});
            int size = m_.vertices_.size();
            m_.indices_.insert(m_.indices_.end(), {0, size-2, size-1});
        }
        int size = m_.vertices_.size();
        m_.indices_.insert(m_.indices_.end(), {0, 1, size-1});
    }
};
