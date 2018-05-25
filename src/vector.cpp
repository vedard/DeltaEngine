#include "vector.hpp"

namespace delta {

Vector::Vector(float x, float y) : x(x), y(y) {}

float Vector::lenght() const { return sqrtf(x * x + y * y); }

float Vector::lenght_squared() const { return x * x + y * y; }

Vector Vector::normalize() const {
    float l = lenght();
    if (l != 0)
        return *this * (1 / l);
    else
        return *this;
}

float Vector::dot(const Vector& v) const { return x * v.x + y * v.y; }

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

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

}  // namespace delta
