#pragma once

#include <numbers>
#include "SDL3/SDL_render.h"

constexpr int kW = 1980; 
constexpr int kH = 1080 ;

constexpr float center_y = kH/2.f; 
constexpr float center_x = kW/2.f;

constexpr SDL_FColor kGray   {0.7f, 0.7f, 0.7f, 1.0f};
constexpr SDL_FColor kYellow {1.0f, 0.9f, 0.0f, 1.0f};
constexpr SDL_FColor kBlue   {0.0f, 0.4f, 1.0f, 1.0f};
constexpr SDL_FColor kOrange {1.0f, 0.4f, 0.0f, 1.0f};
constexpr SDL_FColor kBrown  {0.6f, 0.4f, 0.2f, 1.0f};
constexpr SDL_FColor kRed{1.0f, 0.0f, 0.0f, 1.0f};
constexpr SDL_FColor kWhite{1.0f,1.0f,1.0f,1.0f};

constexpr double kTextScale = 1.3;

constexpr double pi = std::numbers::pi;
constexpr float kG = 1.0f;  
