#pragma once

#include "math/vector.hpp"
#include "shapes/shape.hpp"

namespace dt {

class Body {
   public:
    Vector position;
    Vector velocity;
    Vector forces;

    float angle = 0;
    float angular_velocity = 0;
    float torque = 0;

    float mass = 1.f;
    float inverse_mass = 1.f / 1.f;
    float inertia = 1.f;
    float inverse_inertia = 1.f;

    float density = 1.f;
    float coefficient_restitution = 0.2f;
    float coefficient_static_friction = 0.4f;
    float coefficient_kinetic_friction = 0.2f;

    bool is_static;
    bool is_gravity_affected;

    Shape* shape;

    Body(Vector position, Shape* shape, bool is_gravity_affected, bool is_static);
    void compute_mass();
};

}