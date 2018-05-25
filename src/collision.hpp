#pragma once

#include <vector>
#include "vector.hpp"
#include "body.hpp"

namespace delta {

class Collision {
   public:
    Body *A;
    Body *B;

    Vector normal;
    std::vector<Vector> contacts;

    float peneration;
    float coefficient_restitution;
    float coefficient_static_friction;
    float coefficient_kinetic_friction;

    void Detect();
    void Solve();
};

}  // namespace delta