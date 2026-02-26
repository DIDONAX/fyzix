#include "renderer.h"

#include <print>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"
#include "constants.h"
#include "models.h"
#include "types.h"

Renderer::Renderer(int scale) : scale_(scale) {
    init_sdl();
    init_window();
}

Renderer::~Renderer() {cleanup();}

void Renderer::render(const System& sys) {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    for (const auto& [obj,_] : sys) {
        Circle c(center_.x_ + scale_ * obj->p_.x_, center_.y_ - scale_ * obj->p_.y_, 5 * scale_);
        SDL_RenderGeometry(renderer_, c.m_.texture_, c.m_.vertices_.data(), c.m_.vertices_.size(), c.m_.indices_.data(), c.m_.indices_.size());
    }
    SDL_RenderPresent(renderer_);
}

void Renderer::init_window() {
        SDL_CreateWindowAndRenderer("DDX Engine", kW, kH, SDL_WINDOW_FULLSCREEN, &window_, &renderer_);
        SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED);
        int w, h;
        SDL_GetWindowSize(window_, &w, &h);
        center_ = {w/2.f, h/2.f};
}

void Renderer::init_sdl() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::println("Error: init_sdl()");
    }
}

void Renderer::cleanup() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

SDL_Window* Renderer::get_window() const {
    return window_;
}

SDL_Renderer* Renderer::data() const {
    return renderer_;
}
