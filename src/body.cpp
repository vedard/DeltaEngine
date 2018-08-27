#include "body.hpp"

namespace delta {

Body::Body(math::Vector position, shapes::Shape* shape, bool is_affected_by_gravity, bool is_static)
    : position(position), is_static(is_static), is_affected_by_gravity(is_affected_by_gravity), shape(shape) {
    this->shape->body = this;
    this->calculate_mass();
}

void Body::calculate_mass() {
    if (this->is_static) {
        this->mass = INFINITY;
        this->inverse_mass = 0.f;
    } else {
        this->mass = this->shape->get_area() * this->density;
        this->inverse_mass = 1.f / this->mass;
    }
}

}  // namespace delta