#ifndef PRISM_BSP_HPP_
#define PRISM_BSP_HPP_

#include "prism_export.h"

#include "Prism/objects/objects.hpp"
#include "Prism/scene/acceleration.hpp"
#include "Prism/core/vector.hpp"
#include <memory>
#include <vector>

namespace Prism {

/**
 * @class BSPNode
 * @brief Node for the BSP tree.
 */
class BSPNode {
  public:
    // Plane equation: ax + by + cz + d = 0
    // For simplicity, we use a normal and a distance.
    Vector3 normal;
    double d;
    std::unique_ptr<BSPNode> front;
    std::unique_ptr<BSPNode> back;
    std::vector<Object*> objects;

    BSPNode() = default;
    BSPNode(const Vector3& n, double dist) : normal(n), d(dist) {}
    bool is_leaf() const { return !front && !back; }
};

/**
 * @class BSPTree
 * @brief Binary Space Partitioning acceleration structure.
 */
class PRISM_EXPORT BSPTree : public AccelerationStructure {
  public:
    BSPTree(const std::vector<Object*>& scene_objects);

    virtual bool hit_closest(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override;
    virtual bool hit_any(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override;

  private:
    std::unique_ptr<BSPNode> root;

    void build(BSPNode* node, const std::vector<Object*>& node_objects, int depth = 0);

    bool hit_closest_recursive(const BSPNode* node, const Ray& ray, double t_min, double t_max, HitRecord& rec) const;
    bool hit_any_recursive(const BSPNode* node, const Ray& ray, double t_min, double t_max, HitRecord& rec) const;
};

} // namespace Prism

#endif // PRISM_BSP_HPP_