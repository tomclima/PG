#include <gtest/gtest.h>
#include "Prism/camera.hpp"
#include "Prism/point.hpp"
#include "Prism/vector.hpp"
#include "Prism/matrix.hpp"

using Prism::Camera;
using Prism::Point3;
using Prism::Vector3;
using Prism::Matrix;
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
