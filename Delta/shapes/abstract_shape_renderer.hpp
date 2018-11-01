#pragma once

namespace dt {

class Circle;
class Rectangle;
class Shape;

class AbstractShapeRenderer {
   public:
    virtual void render(Circle *shape) = 0;
    virtual void render(Shape *shape) = 0;
};

}  // namespace dt
