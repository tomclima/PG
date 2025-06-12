#ifndef PRISM_CAMERA_HPP_
#define PRISM_CAMERA_HPP_

#include "prism_export.h"
#include "Prism/point.hpp"
#include "Prism/ray.hpp"
#include "Prism/vector.hpp"
#include <initializer_list>
#include <iterator>
namespace Prism {

using ld = long double;

template <typename T> class Matrix;

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
     * @param viewport_height The height of the viewport (projection screen).
     * @param viewport_width The width of the viewport (projection screen).
     * @param image_height The height of the image in pixels.
     * @param image_width The width of the image in pixels.
     */
     Camera(const Point3& position, const Point3& target, const Vector3& upvec, const ld& distance,
           const ld& viewport_height, const ld& viewport_width, int image_height, int image_width);
    
    ~Camera();

    class CameraIterator {
      public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Ray;
        using difference_type = std::ptrdiff_t;
        using pointer = Ray*;
        using reference = Ray&;

        CameraIterator(Camera* cam, int y, int x) : camera(cam), current_y(y), current_x(x) {
        }

        Ray operator*() const {
            Point3 pixel_center = *camera->pixel_00_loc + (*camera->pixel_delta_u * current_x) -
                          (*camera->pixel_delta_v * current_y);

            return Ray(*camera->pos, pixel_center);
        }

        CameraIterator& operator++() {
            current_x++;
            if (current_x >= camera->pixel_width) {
                current_x = 0;
                current_y++;
            }
            return *this;
        }

        bool operator!=(const CameraIterator& other) const {
            return current_y != other.current_y || current_x != other.current_x;
        }

      private:
        Camera* camera;
        int current_y;
        int current_x;
        
    };

    CameraIterator begin() {
        return CameraIterator(this, 0, 0);
    }
    CameraIterator end() {
        return CameraIterator(this, pixel_height, 0);
    }

    Point3* pos;
    Point3* aim;
    Vector3* up;

    Matrix<ld>* coordinate_basis;

    ld screen_distance;
    ld screen_height;
    ld screen_width;

    int pixel_height;
    int pixel_width;

  private:
    Point3* pixel_00_loc;
    Vector3* pixel_delta_u;
    Vector3* pixel_delta_v;

};

} // namespace Prism

#endif // PRISM_POINT_HPP_