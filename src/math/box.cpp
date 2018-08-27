#include "box.hpp"

namespace delta {
namespace math {

Box::Box(Vector position, Vector size) : position(position), size(size) {
}

bool Box::is_colliding_with(const Box& other) const {
    return (position.x < other.position.x + other.size.x && position.x + size.x > other.position.x &&
            position.y < other.position.y + other.size.y && position.y + size.y > other.position.y);
}

}  // namespace math
}  // namespace delta