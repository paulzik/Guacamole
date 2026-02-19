#include "ECS/Transform.h"
#include "ECS/Entity.h"
#include "Gizmos/Gizmos.h"
#include "Gizmos/GizmoDrawerRegistry.h"
#include "BoxColliderGizmoDrawer.h"
#include "BoxCollider.h"

void BoxColliderGizmoDrawer::DrawGizmos(Entity* entity)
{
    Transform* transform = entity->TryGetComponent<Transform>();
    if (!transform) return;

    Collider* collider = entity->TryGetComponent<Collider>();
    if (!collider) return;

    Gizmos::DrawBox(transform->position, collider->colliderDescriptor.halfExtend * glm::vec3(2), glm::vec3(0, 1, 0));

}

REGISTER_GIZMO_DRAWER(BoxCollider, BoxColliderGizmoDrawer);
