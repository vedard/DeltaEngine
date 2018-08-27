#pragma once

namespace delta {

class Material {
    float density = 1.f;
    float coefficient_restitution = 0.5f;
    float coefficient_static_friction = 1.f;
    float coefficient_kinetic_friction = 1.f;

    static Material Wood();
    static Material Metal();
    static Material Plastic();
};

}  // namespace delta