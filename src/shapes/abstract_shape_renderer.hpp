#pragma once

namespace delta {
namespace shapes {

class Circle;
class Rectangle;
class Shape;

class AbstractShapeRenderer {
   public:
    virtual void render(Circle *shape) = 0;
    // virtual void render(Rectangle *shape) = 0;
    virtual void render(Shape *shape) = 0;
};

}  // namespace shapes
}  // namespace delta
