#include "Prism/utils.hpp"
#include "Prism/point.hpp"
#include "TestHelpers.hpp"
#include <gtest/gtest.h>
#include <vector>

using Prism::Point3;
using Prism::centroid;
using ld = long double;

TEST(UtilsTest, CentroidOfMultiplePoints) {
    Point3 p1(0.0, 0.0, 0.0);
    Point3 p2(9.0, 3.0, 0.0);
    Point3 p3(0.0, 6.0, 12.0);

    Point3 expected_centroid(3.0, 3.0, 4.0);

    Point3 calculated_centroid = centroid({p1, p2, p3});

    AssertPointAlmostEqual(calculated_centroid, expected_centroid);
}

TEST(UtilsTest, CentroidOfSinglePoint) {
    Point3 p1(10.5, -20.0, 30.1);

    Point3 expected_centroid(10.5, -20.0, 30.1);

    Point3 calculated_centroid = centroid({p1});

    AssertPointAlmostEqual(calculated_centroid, expected_centroid);
}

TEST(UtilsTest, CentroidOfSymmetricPoints) {
    Point3 p1(10.0, 10.0, 10.0);
    Point3 p2(-10.0, -10.0, -10.0);

    Point3 expected_centroid(0.0, 0.0, 0.0);

    Point3 calculated_centroid = centroid({p1, p2});

    AssertPointAlmostEqual(calculated_centroid, expected_centroid);
}

TEST(UtilsTest, CentroidThrowsOnEmptyList) {
    // Verify that calling centroid with an empty list of points throws an invalid_argument exception.
    ASSERT_THROW(centroid({}), std::invalid_argument);
}