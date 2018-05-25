#include "world.hpp"

namespace delta {

void World::step() {
    for (Body* body_a : bodies) {
        for (Body* body : bodies) {
        }
    }

    for (Body* body : bodies) {
        body->velocity += body->forces * body->inverse_mass + gravity;
        body->angular_velocity += body->torque * body->inverse_mass;
    }

    for (Body* body : bodies) {
        body->position += body->velocity;
        body->angle += body->angular_velocity;
    }

    for (Body* body : bodies) {
        body->forces = Vector(0, 0);
        body->torque = 0;
    }
}

}  // namespace delta