#pragma once

#include "math/vector.hpp"
#include "shapes/shape.hpp"

namespace delta {

class Body {
   public:
    math::Vector position;
    math::Vector velocity;
    math::Vector forces;

    float angle = 0;
    float angular_velocity = 0;
    float torque = 0;

    float mass = 1000.f;
    float inverse_mass = 1.f / 1000.f;
    float inertia = 1.f;
    float inverse_inertia = 1.f;

    float density = 100.f;
    float coefficient_restitution = 0.2f;
    float coefficient_static_friction = 0.4f;
    float coefficient_kinetic_friction = 0.2f;

    bool is_static;
    bool is_affected_by_gravity;

    shapes::Shape* shape;

    Body(math::Vector position, shapes::Shape* shape, bool is_affected_by_gravity, bool is_static);
    void calculate_mass();
};

}  // namespace delta