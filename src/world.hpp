#pragma once

#include <vector>
#include "math/vector.hpp"
#include "collision.hpp"
#include "body.hpp"

namespace delta {

class Collision;
class World {
   public:
    std::vector<Body*> bodies;
    std::vector<Collision> collisions;

    int velocity_solving_iteration = 30;
    int position_solving_iteration = 1;
    float delta_time = 1.0f / 60.0f;
    math::Vector gravity = math::Vector(0, 1000);

    void step();
};

}  // namespace delta