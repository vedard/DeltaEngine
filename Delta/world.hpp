#pragma once

#include <vector>
#include "body.hpp"
#include "collision.hpp"
#include "math/vector.hpp"

namespace dt {

class Collision;
class World {
   public:
    // List of bodies to update in the next step
    std::vector<Body*> bodies;

    // List of collision for the current step
    std::vector<Collision> collisions;

    // Number of iteration when solving velocity (Higher for more accurate result)
    int velocity_solving_iteration = 8;

    // Number of iteration when solving position (Higher for more accurate result)
    int position_solving_iteration = 1;

    // Time between 2 steps
    float delta_time = 1.0f / 60.0f;

    // The gravity (acceleration) that is applied to the body (meters/seconds)
    Vector gravity = Vector(0.f, 9.8f);

    // Compute the next step and update every bodies in the world
    void step();
};

}  // namespace dt