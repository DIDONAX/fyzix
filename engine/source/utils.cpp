#include "utils.h"
#include "SDL3/SDL_rect.h"

void to_pixel(vec2& pos, vec2& center, float scale) {
    pos.x_ = center.x_ + pos.x_ * scale;
    pos.y_ = center.y_ - pos.y_ * scale;
} 
