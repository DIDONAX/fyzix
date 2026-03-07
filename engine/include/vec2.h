#pragma once

#include <cmath>
namespace fyzix  {

struct vec2 {
    float x_, y_;

    vec2(const float x, const float y) : x_(x), y_(y) {}

    vec2() : x_(0), y_(0) {}

    vec2 operator*(const float s) const {return vec2(x_*s, y_*s);}

    vec2 operator+(const vec2& other) const {return vec2(x_+other.x_, y_+other.y_);}

    vec2 operator-(const vec2& other) const {return vec2(x_-other.x_, y_-other.y_);}

    void operator*=(float s) {
        x_ *= s;
        y_ *= s;
    }

    void operator+=(const vec2& other) {
        x_ += other.x_;
        y_ += other.y_;
    }

    void operator-=(const vec2& other) {
        x_ -= other.x_;
        y_ -= other.y_;
    }

    float length() const {return std::sqrt(x_*x_+ y_*y_);}

    void invert() {(*this)*= -1;}

    void normalize() {
        float l = length();
        if (l == 0) return;
        (*this)*= (1/l);
    }
};

inline vec2 component_product(const vec2& v1, const vec2& v2) {
    return vec2(v1.x_*v2.x_, v1.y_*v2.y_);
}

// scaled by the length of v
inline vec2 normal(const vec2& v) {
    return vec2(v.y_, v.x_);
}

inline float dot_product(const vec2& v1, const vec2& v2) {
    return v1.x_*v2.x_+v1.y_*v2.y_;
}
}
