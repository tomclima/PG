#include "utils.hpp"

void AssertPointAlmostEqual(const Prism::Point3& p1, const Prism::Point3& p2, ld eps) {
    ASSERT_NEAR(p1.x, p2.x, eps);
    ASSERT_NEAR(p1.y, p2.y, eps);
    ASSERT_NEAR(p1.z, p2.z, eps);
}

void AssertVectorAlmostEqual(const Prism::Vector3& v1, const Prism::Vector3& v2, ld eps) {
    ASSERT_NEAR(v1.x, v2.x, eps);
    ASSERT_NEAR(v1.y, v2.y, eps);
    ASSERT_NEAR(v1.z, v2.z, eps);
}