#ifndef PRISM_CAMERA_HPP_
#define PRISM_CAMERA_HPP_

#include "prism_export.h"
#include <initializer_list>
namespace Prism {

using ld = long double;

class Vector3; // Forward declaration of Vector3 class
class Point3;
template<typename T>
class Matrix;

/**
 * @class Camera
 * @brief Represents a camera in 3D space
 * 
 * The Point3 class represents a point in 3D space with x, y, and z coordinates.
 */
class PRISM_EXPORT Camera {
  public:
    /**
     * @brief Constructs a Camera with specified parameters.
     * @param position The starting position of the camera in 3D space.
     * @param target The point at which the camera is aiming (the look-at target).
     * @param upvec The up direction vector that starts from the camera and points upwards.
     * @param distance The distance between the camera and the projection screen (view plane).
     * @param height The physical height of the screen (view plane).
     * @param width The physical width of the screen (view plane).
     */
    Camera(const Point3 &position, const Point3 &target, const Vector3 &upvec, const ld& distance, const ld& height, const ld&width);

    
    Point3 *pos;
    Point3 *aim;
    Vector3 *up;

    Matrix<ld> *coordinate_basis;

    ld screen_distance;
    ld screen_height;
    ld screen_width;


};

} // namespace Prism

#endif // PRISM_POINT_HPP_