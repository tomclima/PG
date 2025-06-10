#include "Prism/utils.hpp"
#include <cstddef>
#include <stdexcept>

namespace Prism {

Point3 centroid(const std::initializer_list<Point3>& points) {
    ld sumX = 0, sumY = 0, sumZ = 0;
    size_t count = points.size();

    if (count == 0) {
        throw std::invalid_argument("Cannot compute centroid of an empty list of points.");
    }

    for (const auto& point : points) {
        sumX += point.x;
        sumY += point.y;
        sumZ += point.z;
    }

    return Point3(sumX / count, sumY / count, sumZ / count);
}

} // namespace Prism