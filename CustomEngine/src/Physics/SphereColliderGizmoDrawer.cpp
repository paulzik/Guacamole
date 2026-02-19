#include "ECS/Transform.h"
#include "ECS/Entity.h"
#include "Gizmos/Gizmos.h"
#include "Gizmos/GizmoDrawerRegistry.h"
#include "SphereColliderGizmoDrawer.h"
#include "SphereCollider.h"

void SphereColliderGizmoDrawer::DrawGizmos(Entity* entity)
{
    Transform* transform = entity->TryGetComponent<Transform>();
    if (!transform) return;

    Collider* collider = entity->TryGetComponent<Collider>();
    if (!collider) return;

    Gizmos::DrawSphere(transform->position, collider->colliderDescriptor.radius, glm::vec3(0, 1, 0));
}

REGISTER_GIZMO_DRAWER(SphereCollider, SphereColliderGizmoDrawer);
