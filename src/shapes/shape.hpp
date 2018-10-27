#pragma once

#include "abstract_shape_renderer.hpp"
#include "../math/vector.hpp"
#include "../math/box.hpp"
#include <vector>

namespace dt {

class Body;



class Shape {
   public:
    dt::Body *body;
    VectorList points;

    Shape();
    virtual float get_area() const;
    virtual Box get_bounding_box() const;
    virtual Vector get_centroid() const;
    virtual VectorList get_edges() const;
    virtual VectorList get_vertices() const;
    virtual void render(AbstractShapeRenderer *renderer);
};


}