#include "ploter.h"



Ploter::Ploter() : center_({padding, kH-padding}) {
    init_sdl();
    init_window();
}

Ploter::~Ploter() {cleanup();}

void Ploter::plot(const Object& obj) {
    objects_.push_back(obj);
}

void Ploter::show(bool vec = false, bool grid = true) {
    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            break;
        }
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
        SDL_RenderClear(renderer_);
        if (grid) {
            plot_grid();
        }
        plot(vec);

        SDL_RenderPresent(renderer_);
    }
}

void Ploter::plot_grid() {
    // light grid color
    SDL_SetRenderDrawColor(renderer_, 60, 60, 60, 255);

    // vertical lines
    for (int x = 0; x < kW; x += kScale) {
        SDL_RenderLine(renderer_, x, 0, x, kH);
    }

    // horizontal lines
    for (int y = 0; y < kH; y += kScale) {
        SDL_RenderLine(renderer_, 0, y, kW, y);
    }

    // axis in brighter color
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderLine(renderer_, center_.x, 0, center_.x, kH);
    SDL_RenderLine(renderer_, 0, center_.y, kW, center_.y);
}


void Ploter::plot(bool vec) {
    for (const auto& obj_ : objects_) {
        float x0 = center_.x + kScale * obj_.p_.x_;
        float y0 = center_.y - kScale * obj_.p_.y_;

        SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
        SDL_FRect r{x0, y0, 2, 2};
        SDL_RenderFillRect(renderer_, &r);
        if (vec) {
            float vx1 = x0 + kScale * obj_.v_.x_;
            float vy1 = y0 - kScale * obj_.v_.y_;
            SDL_SetRenderDrawColor(renderer_, 0, 255, 0, 255);
            SDL_RenderLine(renderer_, x0, y0 , vx1, vy1); 
        }
    }
}
void Ploter::init_window() {
    SDL_CreateWindowAndRenderer("DDX Ploter", kW, kH, 0, &window_, &renderer_);
}

void Ploter::init_sdl() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::println("Error: init_sdl()");
    }
}
void Ploter::cleanup() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}
