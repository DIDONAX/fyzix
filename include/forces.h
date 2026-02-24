#pragma once

#include <math.h>
#include <optional>
#include "constants.h"
#include "object.h"

constexpr std::nullopt_t NullF = std::nullopt;

struct DragF {
    // density
    float p_;
    // drag coeff
    float Cd_;

    DragF(float p, float Cd) : p_(p), Cd_(Cd) {}
    ~DragF(){}

    void apply(Object& obj) {
        // we ignore cross sectional area
        float A = 1;
        obj.a_.x_+= -0.5f * p_ * Cd_  * A * obj.v_.x_ * std::abs(obj.v_.x_) / obj.m_;
        obj.a_.y_+= -0.5f * p_ * Cd_ * A * obj.v_.y_ * std::abs(obj.v_.y_) /obj.m_;
    };
};

struct GravF {
    Object& o_;

    GravF(Object& o) : o_(o){}
    ~GravF(){}

    void apply(Object& obj) {
        float dx = -obj.p_.x_ + o_.p_.x_;  
        float dy = -obj.p_.y_ + o_.p_.y_;  
        float d2 = dx * dx + dy * dy;
        float k = kG * o_.m_ / d2;

        float inv_d = 1.0f / std::sqrt(d2);
        obj.a_.x_ += k * dx * inv_d;
        obj.a_.y_ += k * dy * inv_d;
    };
 
};

struct SpringF {
    float k_;
    float b_;
    vec2 eq_;

    SpringF(float k, float b, vec2 eq) : k_(k), b_(b), eq_(eq){}
    ~SpringF(){}

    void set_eq (vec2& eq) {
        eq_ = eq;
    }

    void apply(Object& obj) {
        obj.a_.x_ += (-k_ * (obj.p_.x_ - eq_.x_) - b_ * obj.v_.x_) / obj.m_;
        obj.a_.y_ += (-k_ * (obj.p_.y_ - eq_.y_) - b_ * obj.v_.y_) / obj.m_; 
    }
}; 
