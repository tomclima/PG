#include <gtest/gtest.h>
#include "Prism/ray.hpp"
#include "Prism/point.hpp"
#include "Prism/vector.hpp"
#include "Prism/objects.hpp"
#include "TestHelpers.hpp"

using namespace Prism;
using std::vector;

class DummyObject : public Object {
public:
    bool hit(const Ray& ray, ld t_min, ld t_max, HitRecord& rec) const override {
        rec.t = 2.0L;
        rec.p = Point3(1.0L, 1.0L, 1.0L);
        rec.normal = Vector3(0.0L, 1.0L, 0.0L);
        rec.material = nullptr;
        rec.set_face_normal(ray, rec.normal);
        return true;
    }
};

TEST(RayTest, ConstructorWithDirection) {
    Point3 origin(0.0L, 0.0L, 0.0L);
    Vector3 dir(1.0L, 0.0L, 0.0L);
    Ray ray(origin, dir);

    ASSERT_NE(ray.origin, nullptr);
    ASSERT_NE(ray.direction, nullptr);

    EXPECT_DOUBLE_EQ(ray.origin->x, 0.0L);
    EXPECT_DOUBLE_EQ(ray.direction->x, 1.0L);
}

TEST(RayTest, ConstructorWithTarget) {
    Point3 origin(0.0L, 0.0L, 0.0L);
    Point3 target(0.0L, 0.0L, 2.0L);
    Ray ray(origin, target);

    ASSERT_NE(ray.origin, nullptr);
    ASSERT_NE(ray.direction, nullptr);

    EXPECT_DOUBLE_EQ(ray.origin->x, 0.0L);
    EXPECT_DOUBLE_EQ(ray.direction->z, 1.0L); // pointing towards +z
}

TEST(RayTest, DirectionReturnsCorrectPointer) {
    Point3 origin(0.0L, 0.0L, 0.0L);
    Vector3 dir(0.0L, 1.0L, 0.0L);
    Ray ray(origin, dir);

    Vector3* d = ray.Direction();
    ASSERT_NE(d, nullptr);
    EXPECT_DOUBLE_EQ(d->y, 1.0L);
}

TEST(RayTest, GethitFindsIntersection) {
    Point3 origin(0.0L, 0.0L, -5.0L);
    Vector3 dir(0.0L, 0.0L, 1.0L);
    Ray ray(origin, dir);

    DummyObject obj;
    vector<Object*> objects = { &obj };

    ld t_min = 0.001L;
    ld t_max = 1000.0L;

    HitRecord hit = ray.Gethit(objects, t_min, t_max);

    EXPECT_NEAR(hit.t, 2.0L, 1e-9);
    EXPECT_EQ(hit.p.x, 1.0L);
    EXPECT_EQ(hit.p.y, 1.0L);
    EXPECT_EQ(hit.normal.y, -1.0L);
    EXPECT_FALSE(hit.front_face); // Because dot(ray.direction, normal) < 0
}
