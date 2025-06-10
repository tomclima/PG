#include "Prism/point.hpp"
#include "Prism/vector.hpp"
#include "utils.hpp"
#include <gtest/gtest.h>

using Prism::Point3;
using Prism::Vector3;
using ld = long double;

TEST(Point3Test, ConstructorsAndAssignment) {
    Point3 p1(1.0, 2.0, 3.0);
    ASSERT_DOUBLE_EQ(p1.x, 1.0);
    ASSERT_DOUBLE_EQ(p1.y, 2.0);
    ASSERT_DOUBLE_EQ(p1.z, 3.0);

    Point3 p2 = p1;
    AssertPointAlmostEqual(p1, p2);

    Point3 p3(0, 0, 0);
    p3 = p1;
    AssertPointAlmostEqual(p3, p1);
}

TEST(Point3Test, Subtraction) {
    Point3 p1(5, 7, 9), p2(1, 2, 3);
    Vector3 v = p1 - p2;
    AssertVectorAlmostEqual(v, Vector3(4, 5, 6));

    Point3 p3(10, 10, 10);
    Vector3 v2 = p3 - p1;
    AssertVectorAlmostEqual(v2, Vector3(5, 3, 1));
}
