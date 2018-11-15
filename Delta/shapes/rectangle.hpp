#pragma once

#include "shape.hpp"

namespace dt {

class Rectangle : public Shape {
   public:
    Vector size;

    Rectangle(const Vector& size) : size(size) {
        this->points.push_back(Vector(-(size.x / 2.f), -(size.y / 2.f)));
        this->points.push_back(Vector((size.x / 2.f), -(size.y / 2.f)));
        this->points.push_back(Vector((size.x / 2.f), (size.y / 2.f)));
        this->points.push_back(Vector(-(size.x / 2.f), (size.y / 2.f)));
    };

    float get_area() const {
        return size.x * size.y;
    }

    Vector get_centroid() const {
        return this->body->position;
    }
};

}  // namespace dt