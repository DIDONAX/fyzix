#pragma once
#include "vec2.h"


namespace fyzix {

struct particle {
   vec2 position_;
   vec2 velocity_;
   vec2 acceleration_;
   vec2 forces_;
   float damping_;
   float inv_mass_;
   float mass_;

   particle() : acceleration_({0,-10}), damping_(0.995), inv_mass_(0) {};
   void clear_forces() {forces_*= 0.f;}
   void apply_force(const vec2& force) {forces_+= force;}
   void set_mass(const float m) {
      mass_ = m; 
      inv_mass_ = 1.f/m; 
   }
};
}
