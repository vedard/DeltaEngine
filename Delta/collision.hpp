#pragma once

#include <algorithm>
#include <vector>
#include "body.hpp"
#include "math/projection.hpp"
#include "math/vector.hpp"
#include "math/edge.hpp"
#include "shapes/circle.hpp"
#include "shapes/shape.hpp"
#include "world.hpp"

namespace dt {

class World;

class Collision {
   public:
    Body* A;
    Body* B;
    World* world;

    Vector normal;
    VectorList contacts;

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
    bool CircleCircleDetection(Circle* shape_a, Circle* shape_b);
    bool PolygonPolygonDetection(Shape* shape_a, Shape* shape_b);

};

}