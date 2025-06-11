#include "Prism/camera.hpp"
#include "Prism/matrix.hpp"
#include "Prism/point.hpp"
#include "Prism/vector.hpp"
#include "TestHelpers.hpp"
#include <gtest/gtest.h>

using Prism::Camera;
using Prism::Matrix;
using Prism::Point3;
using Prism::Vector3;
using ld = long double;

TEST(CameraTest, Instantiation) {
    // Arrange: create Point3 and Vector3 for constructor parameters
    Point3 position(1.0L, 2.0L, 3.0L);
    Point3 target(4.0L, 5.0L, 6.0L);
    Vector3 upvec(0.0L, 1.0L, 0.0L);

    ld distance = 10.0L;
    ld height = 5.0L;
    ld width = 8.0L;

    // Act: instantiate the Camera
    Camera cam(position, target, upvec, distance, height, width);

    // Assert: verify that pointers are not null and values match
    ASSERT_NE(cam.pos, nullptr);
    ASSERT_NE(cam.aim, nullptr);
    ASSERT_NE(cam.up, nullptr);
    ASSERT_NE(cam.coordinate_basis, nullptr); // Assuming constructor initializes this

    EXPECT_EQ(cam.pos->x, position.x);
    EXPECT_EQ(cam.pos->y, position.y);
    EXPECT_EQ(cam.pos->z, position.z);

    EXPECT_EQ(cam.aim->x, target.x);
    EXPECT_EQ(cam.aim->y, target.y);
    EXPECT_EQ(cam.aim->z, target.z);

    EXPECT_EQ(cam.up->x, upvec.x);
    EXPECT_EQ(cam.up->y, upvec.y);
    EXPECT_EQ(cam.up->z, upvec.z);

    EXPECT_DOUBLE_EQ(cam.screen_distance, distance);
    EXPECT_DOUBLE_EQ(cam.screen_height, height);
    EXPECT_DOUBLE_EQ(cam.screen_width, width);
}

TEST(CameraTest, CoordinateBasisOrthonormal) {
    // Arrange
    Point3 position(1.0L, 2.0L, 3.0L);
    Point3 target(4.0L, 5.0L, 6.0L);
    Vector3 upvec(0.0L, 1.0L, 0.0L);

    ld distance = 10.0L;
    ld height = 5.0L;
    ld width = 8.0L;

    // Act
    Camera cam(position, target, upvec, distance, height, width);
    ASSERT_NE(cam.coordinate_basis, nullptr);

    // Extract basis matrix and columns
    const Matrix<ld>& basis = *cam.coordinate_basis;
    auto getCol = [&](int c) { return Vector3{basis[0][c], basis[1][c], basis[2][c]}; };

    // Expected first basis vector: normalized (position - target)
    Vector3 dir = (position - target).normalize();
    Vector3 b1 = getCol(0);
    Vector3 b2 = getCol(1);
    Vector3 b3 = getCol(2);

    // Assert alignment of first basis
    AssertVectorAlmostEqual(b1, dir);

    // Assert unit length
    ASSERT_NEAR(b1.magnitude(), 1.0L, 1e-9);
    ASSERT_NEAR(b2.magnitude(), 1.0L, 1e-9);
    ASSERT_NEAR(b3.magnitude(), 1.0L, 1e-9);

    // Assert orthogonality
    ASSERT_NEAR(b1.dot(b2), 0.0L, 1e-9);
    ASSERT_NEAR(b1.dot(b3), 0.0L, 1e-9);
    ASSERT_NEAR(b2.dot(b3), 0.0L, 1e-9);
}

TEST(CameraTest,
     BasisHasOpposite) { // verifies if basis contains vector opposite to target - position
    Point3 position(1.0L, 2.0L, 3.0L);
    Point3 target(4.0L, 5.0L, 6.0L);
    Vector3 upvec(0.0L, 1.0L, 0.0L);

    ld distance = 10.0L;
    ld height = 5.0L;
    ld width = 8.0L;

    // Act
    Camera cam(position, target, upvec, distance, height, width);
    ASSERT_NE(cam.coordinate_basis, nullptr);

    // Extract basis matrix and columns
    const Matrix<ld>& basis = *cam.coordinate_basis;
    auto getCol = [&](int c) { return Vector3{basis[0][c], basis[1][c], basis[2][c]}; };

    // Expected first basis vector: normalized (position - target)
    Vector3 dir = (position - target).normalize();
    Vector3 b1 = getCol(0);
    Vector3 b2 = getCol(1);
    Vector3 b3 = getCol(2);

    AssertVectorAlmostEqual(b1, ((target - position) * -1).normalize());
}
