#pragma once

#include "math/vector.hpp"
#include "shapes/shape.hpp"

namespace dt {

class Body {
   public:
    // The position in the world (meters)
    Vector position;

    // The linear speed (meters/seconds)
    Vector velocity;

    // The total linear force applied (Newton)
    Vector forces;

    // The linear damping to reduce the velocity (1/seconds)
    Vector linear_damping = dt::Vector(0.f, 0.f);

    // The rotation (radian)
    float angle = 0.f;

    // The rotational speed (radian/second)
    float angular_velocity = 0.f;

    // The rotational force applied (Newton)
    float torque = 0.f;

    // The rotational damping to reduce the angular velocity (1/seconds)
    float angular_damping = 0.f;

    // Total mass (kilograms)
    float mass = 1.f;

    // Use to speed up calculation
    float inverse_mass = 1.f / 1.f;

    // The rotational inertia
    float inertia = 1.f;

    // Use to speed up calculation
    float inverse_inertia = 1.f;

    // The quantity of mass for a area or shape (kilograms/meters^2)
    float density = 0.65f;

    // Ranges from 0 to 1, where 1 would be a perfectly elastic collision
    float coefficient_restitution = 0.5f;

    // The ratio of the force of friction when they are not moving
    float coefficient_static_friction = 0.4f;

    // The ratio of the force of friction when they are moving
    float coefficient_kinetic_friction = 0.2f;

    // If true, the body is immovable, the mass is infinite
    bool is_static = false;

    // If true, the body will fall by the gravity setup in the world
    bool is_gravity_affected = true;

    // If true, the body won't rotate
    bool fixed_rotation = false;

    Shape* shape;

    Body(Shape* shape);
    Body(Vector position, Shape* shape, bool is_gravity_affected = true, bool is_static = false, bool fixed_rotation = false);

    // Compute the mass and inertia from the size of shape and the density
    void compute_mass();
};

}  // namespace dt