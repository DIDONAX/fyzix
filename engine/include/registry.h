#pragma once

#include "force_gen.h"
#include <vector>

namespace fyzix {

struct registry {
    struct entry {
        particle* particle_;
        force_generator* force_;
    };

    std::vector<entry> data_;

    void remove(particle* p, force_generator* fg);
    void add(particle* p, force_generator* fg);
    void clear();
};

}
