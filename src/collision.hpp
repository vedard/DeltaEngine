#pragma once

#include <algorithm>
#include <vector>
#include "body.hpp"
#include "math/projection.hpp"
#include "math/vector.hpp"
#include "shapes/circle.hpp"
#include "shapes/shape.hpp"
#include "world.hpp"

namespace delta {

class World;

class Collision {
   public:
    Body* A;
    Body* B;
    World* world;

    math::Vector normal;
    math::VectorList contacts;

    float penetration;
    float coefficient_restitution;
    float coefficient_static_friction;
    float coefficient_kinetic_friction;

    Collision(Body* a, Body* b, World* w);
    bool BroadDetection();
    bool NarrowDetection();
    void SolveVelocity();
    void SolvePosition();

   private:
    bool CircleCircleDetection(shapes::Circle* shape_a, shapes::Circle* shape_b);
    bool PolygonPolygonDetection(shapes::Shape* shape_a, shapes::Shape* shape_b);

    math::Vector GetBestEdgeInvolve(shapes::Shape* shape, math::Vector n) const;
    //math::VectorList GetClippedPoint(math::Vector vertex_1, math::Vector vertex_2, math::Vector referance_edge, float something);
};

}  // namespace delta