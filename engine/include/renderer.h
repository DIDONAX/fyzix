#pragma once

#include "SDL3/SDL_video.h"
#include "SDL3/SDL_render.h"

#include "object.h"
#include "constants.h"
#include "types.h"
#include <vector>

class Renderer {
    public:
        Renderer(int scale); 

        ~Renderer();

        void render(const System& objs);
        SDL_Window* get_window() const;
        SDL_Renderer* data() const;

    private:
        SDL_Window* window_;
        SDL_Renderer* renderer_;
        int scale_;
        vec2 center_;

        void init_window();

        void init_sdl();

        void cleanup(); 
};
