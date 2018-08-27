#pragma once

#include "shape.hpp"

namespace delta {
namespace shapes {

class Triangle : public Shape {
   public:
    Triangle(float size) {
        this->points.push_back(math::Vector(-size / 2.f, 0.f));
        this->points.push_back(math::Vector(0.f, -size / 2.f));
        this->points.push_back(math::Vector(size / 2.f, 0.f));
    }
};

}  // namespace shapes
}  // namespace delta