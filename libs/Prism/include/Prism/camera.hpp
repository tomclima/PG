#ifndef PRISM_CAMERA_HPP_
#define PRISM_CAMERA_HPP_

#include "prism_export.h"
#include <initializer_list>
namespace Prism {

using ld = long double;

class Vector3; // Forward declaration of Vector3 class
class Point3;

/**
 * @class Camera
 * @brief Represents a camera in 3D space
 * 
 * The Point3 class represents a point in 3D space with x, y, and z coordinates.
 */
class PRISM_EXPORT Camera {
  public:
    /**
     * @brief Constructs a Point with given x, y, z coordinates.
     * @param position the starting position of the camera
     * @param aiming the point at which the camera is aiming
     * @param vup vector that starts from the camera and point upwards
     */
    Camera(Point3 *position, Point3 *aiming, Vector3 vup);

    /**
     * @brief Copy constructor.
     * @param v The point to copy from.
     */
    Point3(const Point3& p);

    /**
     * @brief Constructs a Point from a Vector3.
     * @param v The vector to convert into a point.
     */
    Point3(const Vector3& v);

    /**
     * @brief Constructs a Point from an initializer list of coordinates.
     * @param coords An initializer list containing the x, y, and z coordinates.
     */
    Point3(std::initializer_list<ld> coords);

    /**
     * @brief Asignment operator.
     * @param p The point to assign from.
     * @return Reference to this point.
     */
    Point3 operator= (const Point3& p);

    /**
     * @brief Checks if two points are equal.
     * @param p The point to compare with.
     * @return True if all coordinates are equal, false otherwise.
     */
    bool operator== (const Point3& p) const;

    /**
     * @brief Gets a vector from this point to another point.
     * @param p The point to get the vector to.
     * @return The vector from this point to the specified point.
     */
    Vector3 operator-(const Point3& p) const;

    /**
     * @brief Adds a vector to this point.
     * @param v The vector to add.
     * @return A new point that is the result of adding the vector to this point.
     */
    Point3 operator+(const Vector3& v) const;

    /**
     * @brief Adds a vector to this point in place.
     * @param v The vector to add.
     * @return Reference to this point after addition.
     */
    Point3 operator+=(const Vector3& v);

    ld x; ///< The x coordinate of the point.
    ld y; ///< The y coordinate of the point.
    ld z; ///< The z coordinate of the point.
};

} // namespace Prism

#endif // PRISM_POINT_HPP_