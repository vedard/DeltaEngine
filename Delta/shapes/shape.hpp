#pragma once

#include <vector>
#include "../math/box.hpp"
#include "../math/vector.hpp"

namespace dt {

class Body;

class Shape {
   public:
    dt::Body *body;
    VectorList points;

    Shape();
    Shape(std::initializer_list<Vector> points);
    virtual float get_area() const;
    virtual Box get_bounding_box() const;
    virtual Vector get_centroid() const;
    virtual VectorList get_edges() const;
    virtual VectorList get_vertices() const;
};

}  // namespace dt