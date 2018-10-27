#include "body.hpp"

namespace dt {

Body::Body(Vector position, Shape* shape, bool is_gravity_affected, bool is_static)
    : position(position), is_static(is_static), is_gravity_affected(is_gravity_affected), shape(shape) {
    this->shape->body = this;
    this->compute_mass();
}

void Body::compute_mass() {
    if (this->is_static) {
        this->mass = INFINITY;
        this->inverse_mass = 0.f;
        this->inertia = INFINITY;
        this->inverse_inertia = 0.f;
    } else {
        this->mass = this->shape->get_area() * this->density;
        this->inverse_mass = 1.f / this->mass;

        Box bounding_box = this->shape->get_bounding_box();

        this->inertia = this->mass * (bounding_box.size.x * bounding_box.size.x + bounding_box.size.y * bounding_box.size.y) / 12.f ;
        this->inverse_inertia = 1.f / this->inertia;
    }
}

}