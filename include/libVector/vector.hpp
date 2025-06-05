#ifndef LIBVECTOR_VECTOR_HPP_
#define LIBVECTOR_VECTOR_HPP_

#include <stdexcept>
#include <cmath>

using ld = long double;

namespace LibVector {

class Vector {
  public:
    Vector(ld x = 0, ld y = 0, ld z = 0) : x(x), y(y), z(z) {}
    Vector(const Vector &v) : x(v.x), y(v.y), z(v.z) {}


    bool operator==(const Vector &v) const {
        return (x == v.x && y == v.y && z == v.z);
    }

    bool operator!=(const Vector &v) const {
        return !(*this == v);
    }
    
    Vector &operator=(const Vector &v) {
        if (this != &v) {
            x = v.x;
            y = v.y;
            z = v.z;
        }
        return *this;
    }

    Vector operator+(const Vector &v) const {
        return Vector(x + v.x, y + v.y, z + v.z);
    }
    
    Vector operator+=(const Vector &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    
    Vector operator+(const ld scalar) const {
        return Vector(x + scalar, y + scalar, z + scalar);
    }

    Vector operator+=(const ld scalar) {
        x += scalar;
        y += scalar;
        z += scalar;
        return *this;
    }

    Vector operator-(const Vector &v) const {
        return Vector(x - v.x, y - v.y, z - v.z);
    }

    Vector operator-=(const Vector &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector operator-(const ld scalar) const {
        return Vector(x - scalar, y - scalar, z - scalar);
    }

    Vector operator-=(const ld scalar) {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        return *this;
    }

    Vector operator*(ld scalar) const {
        return Vector(x * scalar, y * scalar, z * scalar);
    }

    Vector operator*=(ld scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector operator/(ld scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return Vector(x / scalar, y / scalar, z / scalar);
    }

    Vector operator/=(ld scalar) {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero");
        }
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    ld dot(const Vector &v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    ld operator*(const Vector &v) const {
        return dot(v);
    }

    Vector cross(const Vector &v) const {
        return Vector(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    ld magnitude() const {
        return std::sqrt(dot(*this));
    }

    Vector normalize() const {
        ld mag = magnitude();
        if (mag == 0) {
            throw std::invalid_argument("Cannot normalize a zero vector");
        }
        return *this / mag;
    }

  private:
    ld x, y, z;
};

}  // namespace LibVector

#endif  // LIBVECTOR_VECTOR_HPP_