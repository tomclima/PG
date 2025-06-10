#include "Prism/point.hpp"

namespace Prism {

Point3::Point3(ld x, ld y, ld z) : x(x), y(y), z(z) {
}
Point3::Point3(const Point3& p) : x(p.x), y(p.y), z(p.z) {
}

Vector3 Point3::operator-(const Point3& p) const {
    return Vector3(x - p.x, y - p.y, z - p.z);
}

} // namespace Prism