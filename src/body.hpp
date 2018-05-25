#pragma once

#include "vector.hpp"

namespace delta {

class Body {
   public:
    Vector position;
    Vector velocity;
    Vector forces;

    float angle;
    float angular_velocity;
    float torque;
    float radius;

    float mass;
    float inverse_mass;

    float coefficient_restitution;
    float coefficient_static_friction;
    float coefficient_kinetic_friction;

    enum Shape { AABB, CIRCLE };
    Shape shape;
};

}  // namespace delta