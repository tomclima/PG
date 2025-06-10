#ifndef PRISM_OBJECT_HPP_
#define PRISM_OBJECT_HPP_

#include "prism_export.h"
#include "Prism/point.hpp"
#include "Prism/vector.hpp"
#include "Prism/ray.hpp"

namespace Prism {

using ld = long double;

class Ray; // Forward declaration of Ray class
class Material; // Forward declaration of Material class

struct HitRecord {
    Point3 p;
    Vector3 normal;
    ld t;
    Material* material;
    bool front_face;

    inline void set_face_normal(const Ray& ray, const Vector3& outward_normal) {
        front_face = (ray.Direction())->dot(outward_normal) < 0;
        normal = front_face ? outward_normal : outward_normal*-1;
    }
};

class PRISM_EXPORT Object {
  public:
    virtual ~Object() = default;

    /**
     * @brief Checks if a ray hits the object within a given distance range.
     * @param ray The ray to test.
     * @param t_min The minimum distance for a valid hit.
     * @param t_max The maximum distance for a valid hit.
     * @param rec The hit record to be filled upon a collision.
     * @return True if a valid hit was found, false otherwise.
     */
    virtual bool hit(const Ray& ray, ld t_min, ld t_max, HitRecord& rec) const = 0;
};

} // namespace Prism

#endif // PRISM_OBJECT_HPP_