#pragma once

#include "vector.hpp"

namespace dt {

class Box {
   public:
    Vector position;
    Vector size;

    Box(Vector position, Vector size);
    bool is_colliding_with(const Box& other) const;
};

}  // namespace dt
