#include "ECS/Transform.h"
#include "ECS/Entity.h"
#include "Gizmos/Gizmos.h"
#include "Gizmos/GizmoDrawerRegistry.h"
#include "ECS/Scene.h"
#include "ColliderGizmoDrawer.h"
#include "Collider.h"
#include "BoxCollider.h"

void ColliderGizmoDrawer::DrawGizmos(Entity* entity)
{
    Transform* transform = entity->TryGetComponent<Transform>();
    if (!transform) return;

    Collider* collider = entity->TryGetComponent<Collider>();
    if (!collider) return;
    std::cout << "HERER" << std::endl;
    //if (auto box = dynamic_cast<BoxCollider*>(collider)) {
    //    Gizmos::DrawBox(transform->position, box->colliderDescriptor.halfExtend, glm::vec3(0, 1, 0));
    //}
    switch (collider->colliderDescriptor.type) {
    case ColliderType::Box:
    {
        Gizmos::DrawBox(transform->position, collider->colliderDescriptor.halfExtend, glm::vec3(0, 1, 0));
        break;
    }
    case ColliderType::Sphere:
    {
        // Draw sphere using transform->position, collider->radius
        Gizmos::DrawSphere(transform->position, collider->colliderDescriptor.radius, glm::vec3(0, 1, 0));
        break;
    }
    case ColliderType::Capsule:
    {
        // Draw capsule using transform->position, collider->radius, collider->height
        //Gizmos::DrawCapsule(transform->position, collider->colliderDescriptor.radius, collider->height, transform->rotation, glm::vec3(0, 0, 1));
        break;
    }
    default:
        break;
    }
}

REGISTER_GIZMO_DRAWER(Collider, ColliderGizmoDrawer);
