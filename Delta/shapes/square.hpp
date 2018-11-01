#pragma once

#include "rectangle.hpp"

namespace dt {

class Square : public Rectangle {
   public:
    float size;

    Square(float size) : Rectangle(dt::Vector(size, size)){};
};

}  // namespace dt