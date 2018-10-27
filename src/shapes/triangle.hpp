#pragma once

#include "shape.hpp"

namespace dt {


class Triangle : public Shape {
   public:
    Triangle(float size) {
        this->points.push_back(Vector(-size / 2.f, 0.f));
        this->points.push_back(Vector(0.f, -size / 2.f));
        this->points.push_back(Vector(size / 2.f, 0.f));
    }
};


}