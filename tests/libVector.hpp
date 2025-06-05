#include "libVector/vector.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <iostream>

using LibVector::Vector;
using ld = long double;

bool almost_equal(ld a, ld b, ld eps = 1e-10) {
    return std::abs(a - b) < eps;
}

bool vector_almost_equal(const Vector& v1, const Vector& v2, ld eps = 1e-10) {
    return almost_equal(v1.x, v2.x, eps) &&
           almost_equal(v1.y, v2.y, eps) &&
           almost_equal(v1.z, v2.z, eps);
}

void test_constructors_and_assignment() {
    Vector v1(1.0, 2.0, 3.0);
    assert(almost_equal(v1.x, 1.0));
    assert(almost_equal(v1.y, 2.0));
    assert(almost_equal(v1.z, 3.0));

    Vector v2 = v1;
    assert(v2 == v1);

    Vector v3(0, 0, 0);
    v3 = v1;
    assert(v3 == v1);
}

void test_equality_operators() {
    Vector v1(1, 2, 3), v2(1, 2, 3), v3(3, 2, 1);
    assert(v1 == v2);
    assert(!(v1 != v2));
    assert(v1 != v3);
}

void test_addition() {
    Vector v1(1, 2, 3), v2(4, 5, 6);
    Vector v3 = v1 + v2;
    assert(v3 == Vector(5, 7, 9));

    v1 += v2;
    assert(v1 == Vector(5, 7, 9));

    Vector v4 = v3 + 1.5;
    assert(v4 == Vector(6.5, 8.5, 10.5));

    v3 += 2.0;
    assert(v3 == Vector(7, 9, 11));
}

void test_subtraction() {
    Vector v1(5, 7, 9), v2(1, 2, 3);
    Vector v3 = v1 - v2;
    assert(v3 == Vector(4, 5, 6));

    v1 -= v2;
    assert(v1 == Vector(4, 5, 6));

    Vector v4 = v3 - 2.0;
    assert(v4 == Vector(2, 3, 4));

    v3 -= 1.0;
    assert(v3 == Vector(3, 4, 5));
}

void test_scalar_multiplication_and_division() {
    Vector v1(1, 2, 3);
    Vector v2 = v1 * 2.0;
    assert(v2 == Vector(2, 4, 6));

    v2 *= 0.5;
    assert(vector_almost_equal(v2, Vector(1, 2, 3)));

    Vector v3 = v1 / 2.0;
    assert(vector_almost_equal(v3, Vector(0.5, 1, 1.5)));

    v3 /= 0.5;
    assert(vector_almost_equal(v3, Vector(1, 2, 3)));

    // Division by zero should throw
    bool caught = false;
    try {
        v1 / 0.0;
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    assert(caught);

    caught = false;
    try {
        v1 /= 0.0;
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    assert(caught);
}

void test_dot_and_cross() {
    Vector v1(1, 2, 3), v2(4, -5, 6);

    ld dot = v1.dot(v2);
    assert(almost_equal(dot, 1*4 + 2*(-5) + 3*6));
    assert(almost_equal(v1 * v2, dot));

    Vector cross = v1.cross(v2);
    Vector expected(27, 6, -13);
    assert(vector_almost_equal(cross, expected));
}

void test_magnitude_and_normalize() {
    Vector v1(3, 4, 0);
    ld mag = v1.magnitude();
    assert(almost_equal(mag, 5.0));

    Vector norm = v1.normalize();
    assert(almost_equal(norm.magnitude(), 1.0));
    assert(vector_almost_equal(norm, Vector(0.6, 0.8, 0.0)));

    // Normalizing zero vector should throw
    Vector zero(0, 0, 0);
    bool caught = false;
    try {
        zero.normalize();
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    assert(caught);
}

void libVectorTest() {
    test_constructors_and_assignment();
    test_equality_operators();
    test_addition();
    test_subtraction();
    test_scalar_multiplication_and_division();
    test_dot_and_cross();
    test_magnitude_and_normalize();
    
    std::cout << "All libVector test passed!\n";
}