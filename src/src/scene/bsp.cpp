#include "Prism/scene/bsp.hpp"
#include "Prism/core/style.hpp"

#include <algorithm>
#include <limits>

namespace Prism {

namespace {
constexpr int MAX_DEPTH = 16;
constexpr int MAX_OBJECTS_PER_NODE = 5;
}

// Helper: choose splitting axis (cycle through x, y, z)
static int choose_axis(int depth) {
    return depth % 3;
}

// Helper: get center of bounding box along axis
static double get_center(Object* obj, int axis) {
    const auto& bbox = obj->get_bounding_box();
    double min_val, max_val;
    if (axis == 0) {
        min_val = bbox.min.x;
        max_val = bbox.max.x;
    } else if (axis == 1) {
        min_val = bbox.min.y;
        max_val = bbox.max.y;
    } else {
        min_val = bbox.min.z;
        max_val = bbox.max.z;
    }
    return (min_val + max_val) * 0.5;
}

BSPTree::BSPTree(const std::vector<Object*>& scene_objects) {
    root = std::make_unique<BSPNode>();
    build(root.get(), scene_objects, 0);
}

void BSPTree::build(BSPNode* node, const std::vector<Object*>& node_objects, int depth) {
    if (node_objects.size() <= MAX_OBJECTS_PER_NODE || depth >= MAX_DEPTH) {
        node->objects = node_objects;
        return;
    }

    int axis = choose_axis(depth);

    // Sort objects by center along axis
    std::vector<Object*> sorted_objects = node_objects;
    std::sort(sorted_objects.begin(), sorted_objects.end(),
        [axis](Object* a, Object* b) {
            return get_center(a, axis) < get_center(b, axis);
        });

    size_t median = sorted_objects.size() / 2;
    double split_value = get_center(sorted_objects[median], axis);

    // Plane normal
    Vector3 normal(0, 0, 0);
    if (axis == 0) normal.x = 1.0;
    else if (axis == 1) normal.y = 1.0;
    else normal.z = 1.0;
    node->normal = normal;
    node->d = -split_value;

    // Partition objects
    std::vector<Object*> front_objects, back_objects;
    for (auto obj : sorted_objects) {
        const auto& bbox = obj->get_bounding_box();
        double min_axis, max_axis;
        if (axis == 0) {
            min_axis = bbox.min.x;
            max_axis = bbox.max.x;
        } else if (axis == 1) {
            min_axis = bbox.min.y;
            max_axis = bbox.max.y;
        } else {
            min_axis = bbox.min.z;
            max_axis = bbox.max.z;
        }

        if (max_axis < split_value)
            back_objects.push_back(obj);
        else if (min_axis > split_value)
            front_objects.push_back(obj);
        else {
            // Straddles the plane, put in both
            front_objects.push_back(obj);
            back_objects.push_back(obj);
        }
    }

    if (!front_objects.empty()) {
        node->front = std::make_unique<BSPNode>();
        build(node->front.get(), front_objects, depth + 1);
    }
    if (!back_objects.empty()) {
        node->back = std::make_unique<BSPNode>();
        build(node->back.get(), back_objects, depth + 1);
    }
}

bool BSPTree::hit_closest(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
    bool hit_anything = false;
    rec.t = t_max;
    if (hit_closest_recursive(root.get(), ray, t_min, rec.t, rec)) {
        hit_anything = true;
    }
    return hit_anything;
}

bool BSPTree::hit_closest_recursive(const BSPNode* node, const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
    if (!node) return false;

    bool hit_anything = false;
    double closest_so_far = t_max;

    if (node->is_leaf()) {
        for (const auto& object : node->objects) {
            if (object->hit(ray, t_min, closest_so_far, rec)) {
                hit_anything = true;
                closest_so_far = rec.t;
            }
        }
        return hit_anything;
    }

    // Decide which side of the plane the ray origin is on
    double origin_side = (node->normal).dot(ray.origin()) + node->d;
    double dir_side = node->normal.dot(ray.direction());

    const BSPNode* first = nullptr;
    const BSPNode* second = nullptr;
    if (origin_side >= 0) {
        first = node->front.get();
        second = node->back.get();
    } else {
        first = node->back.get();
        second = node->front.get();
    }

    // Traverse first side
    if (hit_closest_recursive(first, ray, t_min, closest_so_far, rec)) {
        hit_anything = true;
        closest_so_far = rec.t;
    }

    // Compute intersection with plane
    if (dir_side != 0.0) {
        double t_plane = -(node->normal.dot(ray.origin()) + node->d) / dir_side;
        if (t_plane > t_min && t_plane < closest_so_far) {
            HitRecord temp_rec;
            if (hit_closest_recursive(second, ray, t_min, closest_so_far, temp_rec)) {
                if (temp_rec.t < closest_so_far) {
                    rec = temp_rec;
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                }
            }
        }
    }
    
    return hit_anything;
}

bool BSPTree::hit_any(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
    return hit_any_recursive(root.get(), ray, t_min, t_max, rec);
}

bool BSPTree::hit_any_recursive(const BSPNode* node, const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
    if (!node) return false;
    
    if (node->is_leaf()) {
        for (const auto& object : node->objects) {
            if (object->hit(ray, t_min, t_max, rec)) {
                return true;
            }
        }
        return false;
    }

    double origin_side = node->normal.dot(ray.origin()) + node->d;
    double dir_side = node->normal.dot(ray.direction());

    const BSPNode* first = nullptr;
    const BSPNode* second = nullptr;
    if (origin_side >= 0) {
        first = node->front.get();
        second = node->back.get();
    } else {
        first = node->back.get();
        second = node->front.get();
    }

    if (hit_any_recursive(first, ray, t_min, t_max, rec)) {
        return true;
    }
    
    if (dir_side != 0.0) {
        double t_plane = -(node->normal.dot(ray.origin()) + node->d) / dir_side;
        if (t_plane > t_min && t_plane < t_max) {
            if (hit_any_recursive(second, ray, t_min, t_max, rec)) {
                return true;
            }
        }
    }

    return false;
}

} // namespace Prism