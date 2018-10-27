#include "projection.hpp"

namespace dt {


Projection::Projection(float start, float end) : start(start), end(end) {
}

Projection::Projection(Vector axis, VectorList vertices) {
    start = INFINITY;
    end = -INFINITY;
    for (auto&& vertex : vertices) {
        float point_on_axis = vertex.dot(axis);
        if (point_on_axis < start) {
            start = point_on_axis;
            closest_vertex = vertex;
        }
        if (point_on_axis > end) {
            end = point_on_axis;
            farthest_vertex = vertex;
        }
    }
}

bool Projection::is_overlapping_with(const Projection& other) const {
    return start <= other.end && end >= other.start;
}

float Projection::calculate_overlap_with(const Projection& other) const {
    return std::min(end, other.end) - std::max(start, other.start);
}


}