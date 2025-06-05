#include "libVector/vector.hpp"

#include <stdexcept>
#include <cmath>

using ld = long double;

namespace LibVector {

    Vector::Vector(ld x, ld y, ld z) : x(x), y(y), z(z) {}
    Vector::Vector(const Vector &v) : x(v.x), y(v.y), z(v.z) {}


    bool Vector::operator==(const Vector &v) const {
        return (x == v.x && y == v.y && z == v.z);
    }

    bool Vector::operator!=(const Vector &v) const {
        return !(*this == v);
    }
    
    Vector &Vector::operator=(const Vector &v) {
        if (this != &v) {
            x = v.x;
            y = v.y;
            z = v.z;
        }
        return *this;
    }

    Vector Vector::operator+(const Vector &v) const {
        return Vector(x + v.x, y + v.y, z + v.z);
    }
    
    Vector Vector::operator+=(const Vector &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    
    Vector Vector::operator+(const ld scalar) const {
        return Vector(x + scalar, y + scalar, z + scalar);
    }

    Vector Vector::operator+=(const ld scalar) {
        x += scalar;
        y += scalar;
        z += scalar;
        return *this;
    }

    Vector Vector::operator-(const Vector &v) const {
        return Vector(x - v.x, y - v.y, z - v.z);
    }

    Vector Vector::operator-=(const Vector &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector Vector::operator-(const ld scalar) const {
        return Vector(x - scalar, y - scalar, z - scalar);
    }

    Vector Vector::operator-=(const ld scalar) {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        return *this;
    }

    Vector Vector::operator*(ld scalar) const {
        return Vector(x * scalar, y * scalar, z * scalar);
    }

    Vector Vector::operator*=(ld scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector Vector::operator/(ld scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return Vector(x / scalar, y / scalar, z / scalar);
    }

    Vector Vector::operator/=(ld scalar) {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero");
        }
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    ld Vector::dot(const Vector &v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    ld Vector::operator*(const Vector &v) const {
        return dot(v);
    }

    Vector Vector::cross(const Vector &v) const {
        return Vector(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    ld Vector::magnitude() const {
        return std::sqrt(dot(*this));
    }

    Vector Vector::normalize() const {
        ld mag = magnitude();
        if (mag == 0) {
            throw std::invalid_argument("Cannot normalize a zero vector");
        }
        return *this / mag;
    }


}  // namespace LibVector