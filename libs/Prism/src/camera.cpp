#include "Prism/camera.hpp"
#include "Prism/matrix.hpp"
#include "Prism/objects.hpp"
#include "Prism/point.hpp"
#include "Prism/ray.hpp"
#include "Prism/utils.hpp"
#include "Prism/vector.hpp"
#include <cmath>
#include <stdexcept>

using ld = long double;

namespace Prism {

Camera::Camera(const Point3& position, const Point3& target, const Vector3& upvec,
               const ld& distance, const ld& height, const ld& width) {
    Point3* newpos = new Point3;
    Point3* newaim = new Point3;
    Vector3* newup = new Vector3;

    *newpos = position;
    pos = newpos;

    *newaim = target;
    aim = newaim;

    *newup = upvec;
    up = newup;

    screen_height = height;
    screen_distance = distance;
    screen_width = width;

    Matrix<ld>* newbasis = new Matrix<ld>;

    *newbasis = orthonormalBasisContaining(position - target);

    coordinate_basis = newbasis;
}

void Camera::CastRays(const std ::vector<Object*>& objects) {

    const Matrix<ld>& basis = *coordinate_basis;
    auto getCol = [&](int c) { return Vector3{basis[0][c], basis[1][c], basis[2][c]}; };

    Vector3 x = getCol(1);
    Vector3 y = getCol(2);
    Vector3 z = getCol(0) * (-1) * (screen_distance);

    for (int i = -screen_height / 2; i < screen_height / 2; i++) {
        for (int j = -screen_width / 2; j < screen_width / 2; j++) {
            Vector3 dir = z + (x * i) + (y * j);
            Ray ray(*pos, dir);
            Vector3 color = {0, 0, 0};
            ld t_min = 1;
            ld t_max = 99999;
            HitRecord rec = ray.Gethit(objects, t_min, t_max);
            if (rec.t == t_max) {
                // TODO: Material class to calculate color
            }
        }
    }
}

} // namespace Prism