#pragma once

#include <cmath>
#include <iostream>
#include <vector>

namespace dt {

class Vector {
   public:
    float x;
    float y;

    Vector(float x = 0.f, float y = 0.f);

    // Total length of the vector
    float lenght() const;

    // Total length squared (faster than lenght)
    float lenght_squared() const;

    // Dot product
    float dot(const Vector &v) const;

    // Cross product
    float cross(const Vector &v) const;

    // Angle from the x axis (atan2)
    float angle() const;

    // Cross product from a z value
    Vector cross(const float z) const;

    // Return a normlize vector of length 1
    Vector normalize() const;

    // Return a normal vector
    Vector normal() const;

    Vector operator+(const Vector &v) const;
    Vector operator-(const Vector &v) const;
    Vector operator*(const Vector &v) const;
    Vector operator/(const Vector &v) const;
    Vector operator/(float value) const;
    Vector operator*(float value) const;
    Vector &operator+=(const Vector &v);
    Vector &operator-=(const Vector &v);
    Vector &operator/=(float value);
    Vector &operator*=(float value);
    bool operator==(const Vector &v) const;
    friend std::ostream &operator<<(std::ostream &os, const Vector &v);
};

typedef std::vector<Vector> VectorList;

}  // namespace dt
