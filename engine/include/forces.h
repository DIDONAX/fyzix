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

    void apply(Mass& obj) {
        // we ignore cross sectional area
        float A = 1;
        obj.a_.x_+= -0.5f * p_ * Cd_  * A * obj.v_.x_ * std::abs(obj.v_.x_) / obj.m_;
        obj.a_.y_+= -0.5f * p_ * Cd_ * A * obj.v_.y_ * std::abs(obj.v_.y_) /obj.m_;
    };
};

struct GravF {
    Mass& o_;

    GravF(Mass& o) : o_(o){}
    ~GravF(){}

    void apply(Mass& obj) {
        float dx = -obj.p_.x_ + o_.p_.x_;  
        float dy = -obj.p_.y_ + o_.p_.y_;  
        float d2 = dx * dx + dy * dy;
        float k = kG * o_.m_ / d2;

        float inv_d = 1.0f / std::sqrt(d2);
        obj.a_.x_ += k * dx * inv_d;
        obj.a_.y_ += k * dy * inv_d;
    };
 
};

struct Gravity {
    Gravity(){}
    ~Gravity(){}
    void apply(Mass& obj) {
        obj.a_.y_ -= 9.8f;;
    };
};

struct SpringF {
    float k_;
    float b_;
    Mass* eq_;

    SpringF(float k, float b, Mass& eq) : k_(k), b_(b), eq_(&eq){}
    ~SpringF(){}

    void apply(Mass& obj) {
        obj.a_.x_ += (-k_ * (obj.p_.x_ - eq_->p_.x_) - b_ * obj.v_.x_) / obj.m_;
        obj.a_.y_ += (-k_ * (obj.p_.y_ - eq_->p_.y_) - b_ * obj.v_.y_) / obj.m_; 
    }
}; 
