#pragma once

#include <algorithm>
#include <cmath>
#include "shape.hpp"

namespace delta {
namespace shapes {

class Rectangle : public Shape {
   public:
    math::Vector size;

    Rectangle(math::Vector size) : size(size) {
        this->points.push_back(math::Vector(-(size.x / 2.f), -(size.y / 2.f)));
        this->points.push_back(math::Vector((size.x / 2.f), -(size.y / 2.f)));
        this->points.push_back(math::Vector((size.x / 2.f), (size.y / 2.f)));
        this->points.push_back(math::Vector(-(size.x / 2.f), (size.y / 2.f)));
    };

    float get_area() const {
        return size.x * size.y;
    }

    math::Box get_bounding_box() const {
        return math::Box(body->position - size / 2, body->position + size / 2);
    };
};
}  // namespace shapes
}  // namespace delta