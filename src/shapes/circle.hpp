#pragma once

#include "shape.hpp"

namespace delta {
namespace shapes {

class Circle : public Shape {
   public:
    float radius = 10.f;

    Circle(float radius, int vertex = 15) : radius(radius) {
        float increment = 2.0f * M_PI / vertex;
        for (float angle = 0.0f; angle <= 2.0f * M_PI; angle += increment) {
            this->points.push_back(math::Vector(radius * std::cos(angle), radius * std::sin(angle)));
        }
    }

    float get_area() const {
        return M_PI * radius * radius;
    }

    math::Box get_bounding_box() const {
        return math::Box(math::Vector(body->position.x - radius, body->position.y - radius),
                         math::Vector(radius * 2, radius * 2));
    }

    void render(AbstractShapeRenderer *renderer){
        renderer->render(this);
    }
};

}  // namespace shapes
}  // namespace delta