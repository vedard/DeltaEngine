#include "shape.hpp"
#include "../body.hpp"

namespace delta {
namespace shapes {

Shape::Shape() {
}

float Shape::get_area() const {
    float area = 0.f;

    // Shoelace formula
    size_t j = points.size() - 1;
    for (size_t i = 0; i < points.size(); i++) {
        area += (points[j].x + points[i].x) * (points[j].y - points[i].y);
        j = i;
    }

    return std::fabs(area / 2.0);
}

math::VectorList Shape::get_edges() const {
    math::VectorList _vertices = get_vertices();
    math::VectorList edges;

    for (size_t i = 0; i < _vertices.size() - 1; i++) {
        edges.push_back(_vertices[i + 1] - _vertices[i]);
    }

    edges.push_back(_vertices.front() - _vertices.back());

    return edges;
}
math::VectorList Shape::get_vertices() const {
    math::VectorList _vertices;

    for (auto&& vertex : this->points) {

        _vertices.push_back(math::Vector(
            body->position.x + (vertex.x) * std::cos(body->angle) - (vertex.y) * std::sin(body->angle),
            body->position.y + (vertex.x) * std::sin(body->angle) + (vertex.y) * std::cos(body->angle)
        ));
    }
    return _vertices;
}

void Shape::render(AbstractShapeRenderer* renderer) {
    renderer->render(this);
}

math::Vector Shape::get_centroid() const {
    float x = 0;
    float y = 0;

    for (auto&& vertex : get_vertices()) {
        x += vertex.x;
        y += vertex.y;
    }

    return math::Vector(x / points.size(), y / points.size());
}

math::Box Shape::get_bounding_box() const {
    float minx = INFINITY;
    float miny = INFINITY;
    float maxx = -INFINITY;
    float maxy = -INFINITY;

    for (auto&& vertex : get_vertices()) {
        minx = std::min(minx, vertex.x);
        miny = std::min(miny, vertex.y);
        maxx = std::max(maxx, vertex.x);
        maxy = std::max(maxy, vertex.y);
    }

    return math::Box(math::Vector(minx, miny), math::Vector(maxx - minx, maxy - miny));
}

}  // namespace shapes
}  // namespace delta