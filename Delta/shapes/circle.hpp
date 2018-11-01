#pragma once

#include "ellipse.hpp"

namespace dt {

class Circle : public Ellipse {
   public:
    float radius = 10.f;

    Circle(float radius, int vertex = 16) : Ellipse(radius, radius, vertex), radius(radius) {
    }

     Box get_bounding_box() const {
        return Box(Vector(body->position.x - radius_x, body->position.y - radius_y),
                   Vector(radius_x * 2, radius_y * 2));
    }
};

}  // namespace dt