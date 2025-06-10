#ifndef PRISM_POINT_HPP_
#define PRISM_POINT_HPP_

#include "prism_export.h"
#include "Prism/vector.hpp"

using ld = long double;

namespace Prism {

class PRISM_EXPORT Point3 {
  public:

    Point3(ld x, ld y, ld z);
    Point3(const Point3& p);

    Vector3 operator-(const Point3& p) const;

    ld x, y, z;

};

} // namespace Prism

#endif // PRISM_POINT_HPP_