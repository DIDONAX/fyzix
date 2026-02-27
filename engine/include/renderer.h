#pragma once

#include "SDL3/SDL_video.h"
#include "SDL3/SDL_render.h"

#include "object.h"
#include "constants.h"
#include "types.h"
#include <vector>

struct Renderer {
    Renderer(int scale); 

    ~Renderer();

    void clear() const; 
    void draw(RObject& o);
    void render() const; 
    SDL_Window* get_window() const;
    SDL_Renderer* data() const;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    int scale_;
    vec2 center_;

    void init_window();

    void init_sdl();

    void cleanup(); 
};
