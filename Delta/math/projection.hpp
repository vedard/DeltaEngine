#pragma once

#include <vector>
#include "vector.hpp"

namespace dt {

class Projection {
   public:
    float start;
    float end;
    Vector farthest_vertex;
    Vector closest_vertex;

    Projection(float start, float end);
    Projection(const Vector& axis, const VectorList& vertices);
    bool is_overlapping_with(const Projection& other) const;
    float calculate_overlap_with(const Projection& other) const;
};

}  // namespace dt
