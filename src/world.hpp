#pragma once

#include <vector>
#include "body.hpp"
#include "vector.hpp"

namespace delta {

class World {
   public:
    std::vector<Body*> bodies;

    Vector gravity = Vector(0, 10);

    void step();
};

}  // namespace delta