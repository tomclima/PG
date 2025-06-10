#include "Prism/vector.hpp"
#include "Prism/point.hpp"
#include "Prism/matrix.hpp"
#include "Prism/camera.hpp"
#include "Prism/utils.hpp"
#include <cmath>
#include <stdexcept>

using ld = long double;

namespace Prism {

Camera::Camera(const Point3 &position, const Point3 &target, const Vector3 &upvec, const ld& distance, const ld& height, const ld&width){
    Point3 *newpos = new Point3;
    Point3 *newaim = new Point3;
    Vector3 *newup = new Vector3;

    *newpos = position;
    pos = newpos;

    *newaim = target;
    aim = newaim;

    *newup = upvec;
    up = newup;

    screen_height = height;
    screen_distance = distance;
    screen_width = width;

    Matrix<ld> *newbasis = new Matrix<ld>;

    *newbasis = orthonormalBasisContaining(position - target);
    
    coordinate_basis = newbasis;

}




} // namespace Prism