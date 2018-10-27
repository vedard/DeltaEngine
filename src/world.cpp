#include "world.hpp"
#include "collision.hpp"

namespace dt {

void World::step() {

    // Check for collisions
    collisions.clear();
    for (auto it = bodies.begin(); it != bodies.end(); it++) {
        for (auto it2 = it + 1; it2 != bodies.end(); it2++) {
            Collision c(*it, *it2, this);
            if (c.BroadDetection() && c.NarrowDetection()) {
                collisions.push_back(c);
            }
        }
    }

    // Update velocities
    for (Body* body : bodies) {
        if (!body->is_static) {
            body->velocity += body->forces * body->inverse_mass * delta_time;
            if (body->is_affected_by_gravity) {
                body->velocity += gravity * delta_time;
            }
            body->angular_velocity += body->torque * body->inverse_mass * delta_time;
        }
    }

    // Solve collision velocity
    for (int i = 0; i < this->velocity_solving_iteration; i++) {
        for (auto&& collision : collisions) {
            collision.SolveVelocity();
        }
    }

    // Update positions
    for (Body* body : bodies) {
        if (!body->is_static) {
            body->position += body->velocity * delta_time;
            body->angle += body->angular_velocity * delta_time;

            //body->velocity = (body->velocity) / (1 + 0.0001f);
        }
    }

    // Solve collision position
    for (int i = 0; i < this->position_solving_iteration; i++) {
        for (auto&& collision : collisions) {
            collision.SolvePosition();
        }
    }

    // Reset forces
    for (Body* body : bodies) {
        body->forces = Vector(0, 0);
        body->torque = 0;
    }
}

}