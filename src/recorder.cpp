#include "recorder.h"
#include <format>
#include <print>

Recorder::Recorder(Renderer& r) : frame_(0), renderer_(&r) {}

void Recorder::capture_bmp() {
        SDL_Surface* surface = SDL_RenderReadPixels(renderer_->data(), NULL);
        std::string path = std::format("output/sc-{:04}.bmp", frame_++);
        SDL_SaveBMP(surface, path.data());
        SDL_DestroySurface(surface);
}

void Recorder::load_bmp(const std::string& f) const {
    SDL_Surface* surface = SDL_LoadBMP(f.data());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_->data(), surface);
    SDL_DestroySurface(surface);

    SDL_RenderClear(renderer_->data());
    SDL_RenderTexture(renderer_->data(), texture, NULL, NULL);
    SDL_RenderPresent(renderer_->data());
    SDL_DestroyTexture(texture);
}

void Recorder::play() {
    bool running = true;
    SDL_Event event;
    for (int i = 0; i < frame_ && running; ++i) {
        if(!running) break;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case (SDL_EVENT_QUIT): 
                    running = false;
                    break;
                default:
                    break;
            }
        }
        std::string path = std::format("output/sc-{:04}.bmp", i);
        load_bmp(path);
    }
    std::println("Playback Ended");
}

void Recorder::reset() {
    frame_ = 0;
}
