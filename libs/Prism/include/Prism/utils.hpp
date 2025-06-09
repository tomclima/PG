#ifndef PRISM_UTILS_HPP_
#define PRISM_UTILS_HPP_

#include "prism_export.h"
#include "Prism/point.hpp"
#include <initializer_list>

namespace Prism {
    Point3 PRISM_EXPORT centroid(const std::initializer_list<Point3>& points);
} // namespace Prism



#endif // PRISM_UTILS_HPP_