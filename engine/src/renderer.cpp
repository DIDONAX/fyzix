#include "renderer.h"

#include <print>
#include "SDL3/SDL_init.h"
#include "constants.h"
#include "constraint.h"
#include "forces.h"
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

void Renderer::display() const {
    SDL_RenderPresent(renderer_);
}

void Renderer::draw_grid() {
    int w, h;
    SDL_GetWindowSize(window_, &w, &h);

    // light grid color
    SDL_SetRenderDrawColor(renderer_, 60, 60, 60, 255);

    // vertical lines
    for (int left = center_.x_, right = center_.x_; right <= w; right += scale_, left-= scale_) {
        SDL_RenderLine(renderer_, right, 0, right, h);
        SDL_RenderLine(renderer_, left, 0, left, h);
    }

    // horizontal lines
    for (int up = center_.y_, down = center_.y_; down <= h; down += scale_, up-= scale_) {
        SDL_RenderLine(renderer_, 0, down, w, down);
        SDL_RenderLine(renderer_, 0, up, w, up);
    }

    // axis in brighter color
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderLine(renderer_, center_.x_, 0, center_.x_, h);
    SDL_RenderLine(renderer_, 0, center_.y_, w, center_.y_);
}

void Renderer::draw(std::string& label, float x , float y, float scale) {
    SDL_SetRenderScale(renderer_, kTextScale * scale, kTextScale * scale);
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer_,  x/kTextScale, y/kTextScale, label.data());
    SDL_SetRenderScale(renderer_, 1.0f, 1.0f);
}

void Renderer::draw(const RObject& o, const Constraint& c) {
    vec2 p1 = o.obj_->p_;
    to_pixel(p1, center_ , scale_);

    if (c.has_value()) {
        std::visit([&](auto& c) {
            using T = std::decay_t<decltype(c)>;
            if constexpr (std::is_same_v<T, DistanceC>) {
                vec2 p2 = c.p_->p_;
                to_pixel(p2, center_ , scale_);
                SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
                SDL_RenderLine(renderer_, p1.x_, p1.y_, p2.x_, p2.y_);
            }
        }, *c);
    }
}

void Renderer::draw(const RObject& o, const Force& f) {
    vec2 p1 = o.obj_->p_;
    to_pixel(p1, center_, scale_);

    if (!f.has_value()) return;

    std::visit([&](auto& f) {
        using T = std::decay_t<decltype(f)>;
        if constexpr (std::is_same_v<T, SpringF>) {
            vec2 p2 = f.eq_->p_;
            to_pixel(p2, center_, scale_);

            vec2 dir = { p2.x_ - p1.x_, p2.y_ - p1.y_ };
            float len = std::sqrt(dir.x_ * dir.x_ + dir.y_ * dir.y_);
            if (len == 0.0f) return;

            dir.x_ /= len;
            dir.y_ /= len;

            vec2 normal = { -dir.y_, dir.x_ };

            const int points = 40;
            const float amp = 6.0f;

            SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);

            vec2 prev = p1;
            for (int i = 1; i <= points; ++i) {
                float t = float(i) / points;

                float sin = std::sin(t * 2.0f * M_PI * 6); // 6 coils
                vec2 offset = { normal.x_ * sin * amp, normal.y_ * sin * amp };
                vec2 current = { p1.x_ + dir.x_ * len * t + offset.x_,
                                 p1.y_ + dir.y_ * len * t + offset.y_ };
                SDL_RenderLine(renderer_, prev.x_, prev.y_, current.x_, current.y_);
                prev = current;
            }

            SDL_RenderLine(renderer_, prev.x_, prev.y_, p2.x_, p2.y_);
        }
    }, *f);
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
