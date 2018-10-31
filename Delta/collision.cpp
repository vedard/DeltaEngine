#include "collision.hpp"

namespace dt {

Collision::Collision(Body* a, Body* b) : A(a), B(b) {
}

bool Collision::Detect(){
    return BroadDetection() && NarrowDetection();
}

bool Collision::BroadDetection() {
    if (A == B) return false;  // A and B are the same body

    if (A->is_static && B->is_static) return false;

    if (A->mass == INFINITY && B->mass == INFINITY)
        return false;  // They might be colliding, but they won't move anyway

    // Cheap AABB Test
    if (!A->shape->get_bounding_box().is_colliding_with(B->shape->get_bounding_box())) return false;

    coefficient_restitution = std::min(A->coefficient_restitution, B->coefficient_restitution);
    coefficient_static_friction = std::sqrt(A->coefficient_static_friction * B->coefficient_static_friction);
    coefficient_kinetic_friction = std::sqrt(A->coefficient_kinetic_friction * B->coefficient_kinetic_friction);
    return true;
}

bool Collision::NarrowDetection() {
    if (dynamic_cast<Circle*>(A->shape) && dynamic_cast<Circle*>(B->shape)) {
        return CircleCircleDetection(dynamic_cast<Circle*>(A->shape), dynamic_cast<Circle*>(B->shape));
    } else {
        return PolygonPolygonDetection(A->shape, B->shape);
    }
}

bool Collision::PolygonPolygonDetection(Shape* shape_a, Shape* shape_b) {
    // Separating Axis Theorem (SAT) algorithm to detect polygon collision
    this->penetration = INFINITY;
    this->normal = Vector(0, 0);
    VectorList axes;

    for (auto&& edge : shape_a->get_edges()) axes.push_back(edge.normalize().normal());

    for (auto&& edge : shape_b->get_edges()) axes.push_back(edge.normalize().normal());

    for (auto&& axis : axes) {
        Projection projection_a(axis, shape_a->get_vertices());
        Projection projection_b(axis, shape_b->get_vertices());

        if (projection_a.is_overlapping_with(projection_b)) {
            float overlap = projection_a.calculate_overlap_with(projection_b);
            if (overlap < this->penetration) {
                this->penetration = overlap;
                this->normal = axis;
            }
        } else {
            return false;
        }
    }
    
    if ((shape_b->get_centroid() - shape_a->get_centroid()).dot(this->normal) < 0.f) {
        this->normal = this->normal * -1.f;
    }

    Edge referance_edge = Edge::GetBestEdgeInvolve(shape_a->get_vertices(), this->normal);
    Edge incident_edge = Edge::GetBestEdgeInvolve(shape_b->get_vertices(), this->normal * -1.f);

    // Identify the reference edge and incident edge
    bool flip = false;
    if (std::abs(referance_edge.edge.dot(this->normal)) > std::abs(incident_edge.edge.dot(this->normal))) {
        std::swap(referance_edge, incident_edge);
        flip = true;
    }

    Vector referance_vector = referance_edge.edge.normalize();
    
    float o1 = referance_vector.dot(referance_edge.point_1);
    this->contacts = Edge::GetClippedPoints(incident_edge.point_1, incident_edge.point_2, referance_vector, o1);
    if (this->contacts.size() < 2){
        return true;
    }

    float o2 = referance_vector.dot(referance_edge.point_2);
    this->contacts  = Edge::GetClippedPoints(this->contacts[0], this->contacts[1], referance_vector * -1.f, -o2);
    if (this->contacts.size() < 2) {
        return true;
    }

    Vector reference_normal = referance_edge.edge.cross(-1.f);

    // if (flip){
        // reference_normal *= -1.f;
    // }

    float max = reference_normal.dot(referance_edge.max);

    if (reference_normal.dot(this->contacts[0]) - max < 0.f) {
        this->contacts.erase(std::remove(this->contacts.begin(), this->contacts.end(), this->contacts[0]), this->contacts.end());
    }
    if (reference_normal.dot(this->contacts[1]) - max < 0.f) {
        this->contacts.erase(std::remove(this->contacts.begin(), this->contacts.end(), this->contacts[1]), this->contacts.end());
    }

    return true;
}

bool Collision::CircleCircleDetection(Circle* shape_a, Circle* shape_b) {
    Vector v_distance = B->position - A->position;

    float distance_squared = v_distance.lenght_squared();
    float both_radius = shape_a->radius + shape_b->radius;

    if (distance_squared >= both_radius * both_radius) {
        // no collision
        return false;
    }

    float distance = std::sqrt(distance_squared);

    if (distance == 0.0f) {
        this->penetration = shape_a->radius;
        this->normal = Vector(1, 0);
        this->contacts.push_back(A->position);
    } else {
        this->penetration = both_radius - distance;
        this->normal = v_distance / distance;
        this->contacts.push_back(this->normal * shape_a->radius + A->position);
    }

    return true;
}

void Collision::SolveVelocity() {

    for (auto&& contact : contacts) {

        Vector ra = contact - A->position;
        Vector rb = contact - B->position;
        float raCrossN = ra.cross(normal); 
        float rbCrossN = rb.cross(normal);
    
        float sum_inverse_mass = (A->inverse_mass + B->inverse_mass) + raCrossN * raCrossN * A->inverse_inertia + rbCrossN * rbCrossN * B->inverse_inertia;

        // impact speed
        Vector velocity_difference = B->velocity - A->velocity  + rb.cross(-B->angular_velocity) - ra.cross(-A->angular_velocity);
        float dot = velocity_difference.dot(this->normal);

        // Already Moving away
        if (dot > 0.0f) return;

        // if (this->penetration < 0.1f) this->coefficient_restitution = 0.f;

        // Calculate impulse
        float impulse = (-(1.0f + this->coefficient_restitution) * dot) / sum_inverse_mass / ((float)contacts.size());
        Vector v_impulse = this->normal * impulse;

        // Update velocity
        A->velocity -= (v_impulse * A->inverse_mass);
        A->angular_velocity -= A->inverse_inertia * ra.cross(v_impulse);
        B->velocity += (v_impulse * B->inverse_mass);
        B->angular_velocity += B->inverse_inertia * rb.cross(v_impulse);

        // Friction
        // velocity_difference = B->velocity - A->velocity;
        velocity_difference = B->velocity - A->velocity  + rb.cross(-B->angular_velocity) - ra.cross(-A->angular_velocity);

        Vector tangent = (velocity_difference - (normal * velocity_difference.dot(normal))).normalize();
        float impulse_tangent = velocity_difference.dot(tangent) * -1.f / sum_inverse_mass / ((float)contacts.size());

        // Negligible
        if (std::abs(impulse_tangent) <= 0.001f) return;

        // Coulumb's law
        Vector v_impulse_tangent;
        if (std::abs(impulse_tangent) < impulse * coefficient_static_friction)
            v_impulse_tangent = tangent * impulse_tangent;
        else
            v_impulse_tangent = tangent * -impulse * coefficient_kinetic_friction;

        // Update velocity
        A->velocity -= (v_impulse_tangent * A->inverse_mass);
        A->angular_velocity -= A->inverse_inertia * ra.cross(v_impulse_tangent);
        B->velocity += (v_impulse_tangent * B->inverse_mass);
        B->angular_velocity += B->inverse_inertia * rb.cross(v_impulse_tangent);
    }
}

void Collision::SolvePosition() {
    const float linear_slope = 0.0005f;
    const float max_correction = 0.4f;
    const float correction_percent = 0.8f;

    // for (auto&& contact : contacts) {
        float correction = std::clamp((penetration - linear_slope) * correction_percent, 0.0f, max_correction) /
                        (A->inverse_mass + B->inverse_mass);
        Vector vcorrection = normal * correction;

        // Update position
        A->position -= vcorrection * A->inverse_mass;
        B->position += vcorrection * B->inverse_mass;
    
    // }
}

}
