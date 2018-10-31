#pragma once

#include "math/vector.hpp"
#include "shapes/shape.hpp"

namespace dt {

class Body {
   public:
    Vector position;
    Vector velocity;
    Vector forces;
    float linear_damping = 0.f;

    float angle = 0.f;
    float angular_velocity = 0.f;
    float torque = 0.f;
    float angular_damping = 0.f;

    float mass = 1.f;
    float inverse_mass = 1.f / 1.f;
    float inertia = 1.f;
    float inverse_inertia = 1.f;

    float density = 1.f;
    float coefficient_restitution = 0.2f;
    float coefficient_static_friction = 0.4f;
    float coefficient_kinetic_friction = 0.2f;

    bool is_static = false;
    bool is_gravity_affected = true;
    bool fixed_rotation = false;

    Shape* shape;

    Body(Shape* shape);
    Body(Vector position, Shape* shape, bool is_gravity_affected = true, bool is_static = false, bool fixed_rotation = false);
    void compute_mass();
};

}