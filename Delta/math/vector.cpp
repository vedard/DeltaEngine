#include "vector.hpp"

namespace dt {

Vector::Vector(float x, float y) : x(x), y(y) {
}

float Vector::lenght() const {
    return sqrtf(x * x + y * y);
}

float Vector::lenght_squared() const {
    return x * x + y * y;
}

Vector Vector::normalize() const {
    float l = lenght();
    if (l != 0)
        return *this * (1 / l);
    else
        return *this;
}

Vector Vector::normal() const {
    return Vector(-y, x);
}

float Vector::dot(const Vector& v) const {
    return x * v.x + y * v.y;
}

float Vector::angle() const {
    return atan2f(y, x);
}

float Vector::cross(const Vector& v) const {
    return x * v.y - y * v.x;
}

Vector Vector::cross(const float z) const {
    return Vector(y * z, x * -z);
}

Vector Vector::operator+(const Vector& v) const {
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(const Vector& v) const {
    return Vector(x - v.x, y - v.y);
}

Vector Vector::operator*(const Vector& v) const {
    return Vector(x * v.x, y * v.y);
}

Vector Vector::operator/(const Vector& v) const {
    return Vector(x / v.x, y / v.y);
}

Vector Vector::operator/(float value) const {
    return Vector(x / value, y / value);
}

Vector Vector::operator*(float value) const {
    return Vector(x * value, y * value);
}

Vector& Vector::operator+=(const Vector& v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vector& Vector::operator-=(const Vector& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector& Vector::operator/=(float value) {
    x /= value;
    y /= value;
    return *this;
}

Vector& Vector::operator*=(float value) {
    x *= value;
    y *= value;
    return *this;
}

bool Vector::operator==(const Vector& v) const {
    static const float ELIPSON = 0.0001f;
    return std::fabs(x - v.x) < ELIPSON && std::fabs(y - v.y) < ELIPSON;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

}  // namespace dt
