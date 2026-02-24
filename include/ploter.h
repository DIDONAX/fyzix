#pragma once 

#include "SDL3/SDL_init.h"
#include "constants.h"
#include "object.h"
#include <print>
#include <vector>


struct Ploter {
    public:
        Ploter(); 

        ~Ploter();

        void plot(const Object& obj); 

        void show(bool vec, bool grid);

    private:
        SDL_Window* window_;
        SDL_Renderer* renderer_;
        SDL_Event event;
        SDL_FPoint center_;
        std::vector<Object> objects_;

        void plot_grid(); 
        void plot(bool vec);
        void init_window();

        void init_sdl();
        void cleanup(); 
};
