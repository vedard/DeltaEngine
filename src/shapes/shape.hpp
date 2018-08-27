#pragma once

#include "abstract_shape_renderer.hpp"
#include "../math/vector.hpp"
#include "../math/box.hpp"
#include <vector>

namespace delta {

class Body;

namespace shapes {

class Shape {
   public:
    delta::Body *body;
    math::VectorList points;

    Shape();
    virtual float get_area() const;
    virtual math::Box get_bounding_box() const;
    virtual math::Vector get_centroid() const;
    virtual math::VectorList get_edges() const;
    virtual math::VectorList get_vertices() const;
    virtual void render(AbstractShapeRenderer *renderer);
};

}  // namespace shapes
}  // namespace delta