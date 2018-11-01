#pragma once

#include "shape.hpp"

namespace dt {

class Ellipse : public Shape {
   public:
    float radius_x = 1.f;
    float radius_y = 1.f;

    Ellipse(float radius_x, float radius_y, int vertex = 16) : radius_x(radius_x), radius_y(radius_y) {
        float increment = 2.0f * M_PI / vertex;
        for (float angle = 0.0f; angle <= 2.0f * M_PI; angle += increment) {
            this->points.push_back(Vector(radius_x * std::cos(angle), radius_y * std::sin(angle)));
        }
    }

    float get_area() const {
        return M_PI * radius_x * radius_y;
    }

    Vector get_centroid() const {
        return this->body->position;
    }
};

}  // namespace dt