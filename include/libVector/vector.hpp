#ifndef LIBVECTOR_VECTOR_HPP_
#define LIBVECTOR_VECTOR_HPP_

using ld = long double;

/**
 * @file vector.hpp
 * @brief Defines the Vector class for 3D vector operations in the LibVector namespace.
 */

namespace LibVector {

/**
 * @class Vector
 * @brief Represents a 3-dimensional mathematical vector and provides common vector operations.
 *
 * The Vector class supports arithmetic operations, dot and cross products, normalization,
 * and comparison operators. All operations are performed in 3D space.
 */
class Vector {
    public:
        /**
         * @brief Constructs a Vector with given x, y, z components.
         * @param x The x component (default is 0).
         * @param y The y component (default is 0).
         * @param z The z component (default is 0).
         */
        Vector(ld x = 0, ld y = 0, ld z = 0);

        /**
         * @brief Copy constructor.
         * @param v The vector to copy from.
         */
        Vector(const Vector &v);

        /**
         * @brief Checks if two vectors are equal.
         * @param v The vector to compare with.
         * @return True if all components are equal, false otherwise.
         */
        bool operator==(const Vector &v) const;

        /**
         * @brief Checks if two vectors are not equal.
         * @param v The vector to compare with.
         * @return True if any component differs, false otherwise.
         */
        bool operator!=(const Vector &v) const;

        /**
         * @brief Assignment operator.
         * @param v The vector to assign from.
         * @return Reference to this vector.
         */
        Vector &operator=(const Vector &v);

        /**
         * @brief Adds two vectors.
         * @param v The vector to add.
         * @return The resulting vector.
         */
        Vector operator+(const Vector &v) const;

        /**
         * @brief Adds another vector to this vector.
         * @param v The vector to add.
         * @return Reference to this vector after addition.
         */
        Vector operator+=(const Vector &v);

        /**
         * @brief Adds a scalar to each component of the vector.
         * @param scalar The scalar value to add.
         * @return The resulting vector.
         */
        Vector operator+(const ld scalar) const;

        /**
         * @brief Adds a scalar to each component of this vector.
         * @param scalar The scalar value to add.
         * @return Reference to this vector after addition.
         */
        Vector operator+=(const ld scalar);

        /**
         * @brief Subtracts another vector from this vector.
         * @param v The vector to subtract.
         * @return The resulting vector.
         */
        Vector operator-(const Vector &v) const;

        /**
         * @brief Subtracts another vector from this vector in place.
         * @param v The vector to subtract.
         * @return Reference to this vector after subtraction.
         */
        Vector operator-=(const Vector &v);

        /**
         * @brief Subtracts a scalar from each component of the vector.
         * @param scalar The scalar value to subtract.
         * @return The resulting vector.
         */
        Vector operator-(const ld scalar) const;

        /**
         * @brief Subtracts a scalar from each component of this vector.
         * @param scalar The scalar value to subtract.
         * @return Reference to this vector after subtraction.
         */
        Vector operator-=(const ld scalar);

        /**
         * @brief Multiplies each component of the vector by a scalar.
         * @param scalar The scalar value to multiply by.
         * @return The resulting vector.
         */
        Vector operator*(ld scalar) const;

        /**
         * @brief Multiplies each component of this vector by a scalar in place.
         * @param scalar The scalar value to multiply by.
         * @return Reference to this vector after multiplication.
         */
        Vector operator*=(ld scalar);

        /**
         * @brief Divides each component of the vector by a scalar.
         * @param scalar The scalar value to divide by.
         * @return The resulting vector.
         * @throws std::invalid_argument if scalar is zero.
         */
        Vector operator/(ld scalar) const;

        /**
         * @brief Divides each component of this vector by a scalar in place.
         * @param scalar The scalar value to divide by.
         * @return Reference to this vector after division.
         * @throws std::invalid_argument if scalar is zero.
         */
        Vector operator/=(ld scalar);

        /**
         * @brief Computes the dot product with another vector.
         * @param v The vector to compute the dot product with.
         * @return The dot product (scalar).
         */
        ld dot(const Vector &v) const;

        /**
         * @brief Computes the dot product with another vector (operator overload).
         * @param v The vector to compute the dot product with.
         * @return The dot product (scalar).
         */
        ld operator*(const Vector &v) const;

        /**
         * @brief Computes the cross product with another vector.
         * @param v The vector to compute the cross product with.
         * @return The resulting vector.
         */
        Vector cross(const Vector &v) const;

        /**
         * @brief Computes the magnitude (length) of the vector.
         * @return The magnitude as a scalar.
         */
        ld magnitude() const;

        /**
         * @brief Returns the normalized (unit) vector.
         * @return The normalized vector.
         * @throws std::invalid_argument if the vector is zero.
         */
        Vector normalize() const;

        ld x, y, z; ///< The x, y, and z components of the vector.
};

}  // namespace LibVector

#endif  // LIBVECTOR_VECTOR_HPP_