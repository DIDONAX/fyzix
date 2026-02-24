#include "utils.h"

void to_cartesian(vec2& pos) {
    pos.x_ = (pos.x_ - center_x)/kScale;
    pos.y_ = (center_y - pos.y_)/kScale;
};
