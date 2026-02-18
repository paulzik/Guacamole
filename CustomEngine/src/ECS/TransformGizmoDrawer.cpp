#include "ECS/Transform.h"
#include "ECS/Entity.h"
#include "Gizmos/Gizmos.h"
#include "Gizmos/GizmoDrawerRegistry.h"
#include "ECS/TransformGizmoDrawer.h"

void TransformGizmoDrawer::DrawGizmos(Entity* entity)
{
    if (auto transform = entity->TryGetComponent<Transform>())
    {
        // Y axis arrow
        Gizmos::DrawArrow(
            transform->position,
            transform->position + glm::vec3(0, 1, 0),
            glm::vec3(0.467f, 0.855f, 0.278f)
        );
    }
}

REGISTER_GIZMO_DRAWER(Transform, TransformGizmoDrawer);
