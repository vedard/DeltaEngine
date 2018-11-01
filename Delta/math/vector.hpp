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

    float lenght() const;
    float lenght_squared() const;
    float dot(const Vector &v) const;
    float cross(const Vector &v) const;
    Vector cross(const float z) const;
    Vector normalize() const;
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
