#include "renderer.h"

#include <print>
#include "SDL3/SDL_init.h"
#include "constants.h"
#include "utils.h"


Renderer::Renderer(int scale) : scale_(scale) {
    init_sdl();
    init_window();
}

Renderer::~Renderer() {cleanup();}

void Renderer::clear() const {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

void Renderer::render() const {
    SDL_RenderPresent(renderer_);
}

void Renderer::draw(std::string& label, float x , float y, float scale) {
    SDL_SetRenderScale(renderer_, kTextScale * scale, kTextScale * scale);
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer_,  x/kTextScale, y/kTextScale, label.data());
    SDL_SetRenderScale(renderer_, 1.0f, 1.0f);
}

void Renderer::draw(RObject& ro) {
    auto& indices =  ro.indices_;
    auto& offs = ro.offsets_;
    auto verts =  ro.verts_;

    vec2 p = ro.obj_->p_;
    to_pixel(p, center_ , scale_);

    float off = offs[2];
    float txt_y =  p.y_ - off - 20;

    draw(ro.label_, p.x_, txt_y, 1);

    for (size_t i = 0; i < verts.size(); ++i) {
        verts[i].position.x =  p.x_ + offs[2*i];
        verts[i].position.y =  p.y_ + offs[2*i+1];
    }

    SDL_RenderGeometry(renderer_, nullptr, verts.data(), verts.size(), indices.data(), indices.size());
}

void Renderer::init_window() {
        SDL_CreateWindowAndRenderer("fyzix engine", kW, kH, SDL_WINDOW_FULLSCREEN, &window_, &renderer_);
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
