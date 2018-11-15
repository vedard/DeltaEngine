#pragma once

#include "vector.hpp"

namespace dt {

class Box {
   public:
    Vector position;
    Vector size;

    Box(const Vector& position, const Vector& size);
    bool is_colliding_with(const Box& other) const;
};

}  // namespace dt
