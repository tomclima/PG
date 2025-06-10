#ifndef TESTS_UTILS_HPP
#define TESTS_UTILS_HPP

#include "Prism/point.hpp"
#include "Prism/vector.hpp"
#include <gtest/gtest.h>

using ld = long double;

void AssertPointAlmostEqual(const Prism::Point3& p1, const Prism::Point3& p2, ld eps = 1e-9);
void AssertVectorAlmostEqual(const Prism::Vector3& v1, const Prism::Vector3& v2, ld eps = 1e-9);

#endif // TESTS_UTILS_HPP