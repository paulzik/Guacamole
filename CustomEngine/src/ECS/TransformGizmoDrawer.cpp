#include "ECS/Transform.h"
#include "ECS/Entity.h"
#include "Gizmos/Gizmos.h"
#include "Gizmos/GizmoDrawerRegistry.h"
#include "ECS/TransformGizmoDrawer.h"
#include "ECS/Scene.h"

void TransformGizmoDrawer::DrawGizmos(Entity* entity)
{
    if (auto transform = entity->TryGetComponent<Transform>())
    {
        glm::vec3 localX = transform->rotation * glm::vec3(1, 0, 0);
        glm::vec3 localY = transform->rotation * glm::vec3(0, 1, 0);
        glm::vec3 localZ = transform->rotation * glm::vec3(0, 0, 1);

        if (Scene::Get().axisSystem == AxisSystem::Local) 
        {
            localX = transform->rotation * glm::vec3(1, 0, 0);
            localY = transform->rotation * glm::vec3(0, 1, 0);
            localZ = transform->rotation * glm::vec3(0, 0, 1);
        }
        else 
        {
            localX = glm::vec3(1, 0, 0);
            localY = glm::vec3(0, 1, 0);
            localZ = glm::vec3(0, 0, 1);
        }

        // Y axis arrow
        Gizmos::DrawArrow(transform->position, transform->position + localY, glm::vec3(0.467f, 0.855f, 0.278f));
        // X axis arrow
        Gizmos::DrawArrow(transform->position, transform->position + localX, glm::vec3(0.733f, 0.263f, 0.239f));
        // Z axis arrow
        Gizmos::DrawArrow(transform->position, transform->position + localZ, glm::vec3(0.271f, 0.365f, 0.882f));
    }
}

REGISTER_GIZMO_DRAWER(Transform, TransformGizmoDrawer);
