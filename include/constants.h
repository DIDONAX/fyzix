#pragma once

#include "SDL3/SDL_render.h"
#include <numbers>

constexpr int kW = 1980; 
constexpr int kH = 1080 ;
constexpr int padding = 10;
constexpr float center_y = kH/2.f; 
constexpr float center_x = kW/2.f; 
constexpr SDL_FColor kRed{255, 0, 0, 255};
constexpr SDL_FColor kWhite{255,255,255,255};
constexpr double pi = std::numbers::pi;
// 1unit = kScale px
constexpr float kScale = 1.f;
    // constexpr float kG = 6.674e-11f; 
constexpr float kG = 1.0f;  
