#include "Prism/vector.hpp"
#include "Prism/point.hpp"

#include <cmath>
#include <stdexcept>

using ld = long double;

namespace Prism {

Vector3::Vector3(ld x, ld y, ld z) : x(x), y(y), z(z) {
}

Vector3::Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {
}

Vector3::Vector3(const Point3& v) : x(v.x), y(v.y), z(v.z) {
}

Vector3::Vector3(std::initializer_list<ld> coords) {
    if (coords.size() != 3) {
        throw std::invalid_argument("Initializer list must contain exactly three elements.");
    }
    auto it = coords.begin();
    x = *it++;
    y = *it++;
    z = *it;
}

bool Vector3::operator==(const Vector3& v) const {
    return (x == v.x && y == v.y && z == v.z);
}

bool Vector3::operator!=(const Vector3& v) const {
    return !(*this == v);
}

Vector3& Vector3::operator=(const Vector3& v) {
    if (this != &v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    return *this;
}

Vector3 Vector3::operator+(const Vector3& v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator+=(const Vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3 Vector3::operator+(const ld scalar) const {
    return Vector3(x + scalar, y + scalar, z + scalar);
}

Vector3 Vector3::operator+=(const ld scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator-=(const Vector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3 Vector3::operator-(const ld scalar) const {
    return Vector3(x - scalar, y - scalar, z - scalar);
}

Vector3 Vector3::operator-=(const ld scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    return *this;
}

Vector3 Vector3::operator*(ld scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator*=(ld scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3 Vector3::operator/(ld scalar) const {
    if (scalar == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3 Vector3::operator/=(ld scalar) {
    if (scalar == 0) {
        throw std::invalid_argument("Division by zero");
    }
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

ld Vector3::dot(const Vector3& v) const {
    return x * v.x + y * v.y + z * v.z;
}

ld Vector3::operator*(const Vector3& v) const {
    return dot(v);
}

Vector3 Vector3::cross(const Vector3& v) const {
    return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector3 Vector3::operator^(const Vector3& v) const {
    return cross(v);
}

ld Vector3::magnitude() const {
    return std::sqrt(dot(*this));
}

Vector3 Vector3::normalize() const {
    ld mag = magnitude();
    if (mag == 0) {
        throw std::invalid_argument("Cannot normalize a zero Vector");
    }
    return *this / mag;
}

} // namespace Prism