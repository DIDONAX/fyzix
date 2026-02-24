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

Renderer::Renderer() {
    init_sdl();
    init_window();
}

Renderer::~Renderer() {cleanup();}

void Renderer::render(const System& sys) {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    std::vector<Circle> models;
    for (const auto& [obj,_] : sys) {
        models.emplace_back(center_x + kScale * obj->p_.x_, center_y - kScale * obj->p_.y_, 10.f);
    }
    for (const auto& c : models) {
        SDL_RenderGeometry(renderer_, c.m_.texture_, c.m_.vertices_.data(), c.m_.vertices_.size(), c.m_.indices_.data(), c.m_.indices_.size());
    }
    SDL_RenderPresent(renderer_);
}

void Renderer::init_window() {
        SDL_CreateWindowAndRenderer("DDX Engine", kW, kH, SDL_WINDOW_FULLSCREEN, &window_, &renderer_);
        SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED);
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
