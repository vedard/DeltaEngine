#pragma once

#include "shape.hpp"

namespace dt {


class Square : public Shape {
   public:
    float size;

    Square(float size) : size(size) {
        this->points.push_back(Vector(-(size / 2.f), -(size / 2.f)));
        this->points.push_back(Vector((size / 2.f), -(size / 2.f)));
        this->points.push_back(Vector((size / 2.f), (size / 2.f)));
        this->points.push_back(Vector(-(size / 2.f), (size / 2.f)));
    };

    float get_area() const {
        return size * size;
    }

    Vector get_centroid() const { 
        return this->body->position; 
    }
};

}