#include "registry.h"

namespace fyzix {

void registry::remove(particle* p, force_generator* fg) {
    std::erase_if(data_, [&](entry& e) {
        return p == e.particle_ && fg == e.force_; 
    });
}

void registry::add(particle* p, force_generator* fg) {
    data_.emplace_back(p,fg); 
}

void registry::clear(){
    data_.clear();
}

}
