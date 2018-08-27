#pragma once

#include "vector.hpp"
#include <vector>

namespace delta {
namespace math {

class Edge {
   public:
    Vector max;
    Vector point_1;
    Vector point_2;
    Vector edge;

    Edge(Vector max, Vector p1, Vector p2): max(max), point_1(p1), point_2(p2){
        this->edge = point_2 - point_1;
    }


    static Edge GetBestEdgeInvolve(math::VectorList vertices, math::Vector n){
        Vector current_vertex, previous_vertex, next_vertex;

        // Find the farthest vertex in the collision
        float max = -INFINITY;
        for(size_t i = 0; i < vertices.size(); i++) {
            float projection = n.dot(vertices.at(i));
            if (projection > max) {
                max = projection;
                current_vertex = vertices.at(i);
                previous_vertex = (i == 0) ? vertices.back() : vertices.at(i - 1);
                next_vertex = (i == vertices.size() - 1) ? vertices.front() : vertices.at(i + 1);
            }
        }

        // Find the 2 adjacent edge
        math::Vector left_edge = current_vertex - next_vertex;
        math::Vector right_edge = current_vertex - previous_vertex;

        // The best edge is the most perpendicular to the separation normal.
        if (right_edge.normalize().dot(n) < left_edge.normalize().dot(n)){
            return Edge(current_vertex, previous_vertex, current_vertex);
        } else {
            return Edge(current_vertex, current_vertex, next_vertex);
        }   
    }

    static VectorList GetClippedPoints(Vector v1, Vector v2, Vector normal, float o) {
        VectorList clipped_points;

        float d1 = normal.dot(v1) - o;
        float d2 = normal.dot(v2) - o;

        if (d1 > 0.f)
            clipped_points.push_back(v1);
        if (d2 > 0.f)
            clipped_points.push_back(v2);

        if (d1 * d2 < 0.0) {
            Vector e = v2 - v1;
            double u = d1 / (d1 - d2);
            e *= u;
            e += v1;
            clipped_points.push_back(e);
        }

        return clipped_points;
    }

};

}  // namespace math
}  // namespace delta
