#pragma once
#include "vec2.h"


namespace fyzix {

struct particle {
   vec2 position_;
   vec2 velocity_;
   vec2 acceleration_;
   float damping_;
   float inv_mass_;
   float mass_;

   particle() : damping_(0.995), inv_mass_(0) {};
};

}
