#include "constraint.h"
#include "object.h"
#include <print>

DistanceC::~DistanceC(){}
DistanceC::DistanceC(Mass& p, float dist) : dist_(dist), p_(&p) {}
void DistanceC::apply(Mass& m) {
    vec2 dir = { m.p_.x_ - p_->p_.x_, m.p_.y_ - p_->p_.y_ };

    float len = std::sqrt(dir.x_ * dir.x_ + dir.y_ * dir.y_);
    if (len == 0.0f) return;

    dir.x_ *= 1.0f/len;
    dir.y_ *= 1.0f/len;

    float lambda = dist_ - len;

    m.p_.x_ -= dir.x_ * lambda;
    m.p_.y_ -= dir.y_ * lambda;
}
