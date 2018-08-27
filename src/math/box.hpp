#pragma once

#include "vector.hpp"

namespace delta {
namespace math {

class Box {
   public:
    Vector position;
    Vector size;

    Box(Vector position, Vector size);
    bool is_colliding_with(const Box& other) const;
};

}  // namespace math
}  // namespace delta
