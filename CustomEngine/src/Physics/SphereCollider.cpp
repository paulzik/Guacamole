#include "SphereCollider.h"
#include <glm/vec3.hpp>

ColliderDescription SphereCollider::GetColliderDescription() const
{
    return ColliderDescription(ColliderType::Sphere, glm::vec3(0), m_radius, 0.0f);
}
