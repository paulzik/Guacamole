#include "SelectionSystem.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <limits>
#include <iostream>
#include "imgui.h"
#include "ECS/Scene.h"
#include "ECS/Entity.h"
#include "ECS/MeshFilter.h"
#include "ECS/Transform.h"
#include "ECS/Camera/Camera.h"
#include "Input/Input.h"
#include "Input/Mouse.h"
#include "Utilities/Debug/Debug.h"

bool SelectionSystem::Init()
{
    return true;
}

void SelectionSystem::TryRegister(Component* c)
{
    auto mesh = dynamic_cast<MeshFilter*>(c);
    if (!mesh || mesh->vertices.empty())
        return;

    glm::vec3 min(std::numeric_limits<float>::max());
    glm::vec3 max(std::numeric_limits<float>::lowest());

    for (const Vertex& v : mesh->vertices) {
        min = glm::min(min, v.position);
        max = glm::max(max, v.position);
    }

    pickables.push_back({ mesh, min, max });
}

void SelectionSystem::Update()
{
    Mouse* mouse = Input::GetDevice<Mouse>();
    if (!mouse || !mouse->leftButton.wasPressedThisFrame)
        return;

    //Ignore clicks that land on editor windows
    if (ImGui::GetCurrentContext() && ImGui::GetIO().WantCaptureMouse)
        return;

    Entity* hit = Pick(mouse->position.x, mouse->position.y);
    Scene::Get().selectedEntity = hit;

    if (hit) {
        Debug::Log(std::string("Selected: ") + hit->GetName());
        std::cout << "Selected: " << hit->GetName() << std::endl;
    }
}

void SelectionSystem::Shutdown()
{
    pickables.clear();
}

//Slab test, works with an unnormalized direction
static bool RayIntersectsAABB(const glm::vec3& origin, const glm::vec3& dir,
    const glm::vec3& min, const glm::vec3& max, float& tHit)
{
    float tMin = 0.0f;
    float tMax = std::numeric_limits<float>::max();

    for (int i = 0; i < 3; i++)
    {
        if (glm::abs(dir[i]) < 1e-8f)
        {
            //Ray parallel to this slab, misses unless origin is inside it
            if (origin[i] < min[i] || origin[i] > max[i])
                return false;
        }
        else
        {
            float invD = 1.0f / dir[i];
            float t0 = (min[i] - origin[i]) * invD;
            float t1 = (max[i] - origin[i]) * invD;
            if (t0 > t1) std::swap(t0, t1);

            tMin = glm::max(tMin, t0);
            tMax = glm::min(tMax, t1);

            if (tMin > tMax)
                return false;
        }
    }

    tHit = tMin;
    return true;
}

Entity* SelectionSystem::Pick(float mouseX, float mouseY)
{
    Camera* camera = Scene::Get().GetCamera();
    if (!camera)
        return nullptr;

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    if (viewport[2] <= 0 || viewport[3] <= 0)
        return nullptr;

    //Screen position -> NDC
    float ndcX = 2.0f * (mouseX - viewport[0]) / viewport[2] - 1.0f;
    float ndcY = 1.0f - 2.0f * (mouseY - viewport[1]) / viewport[3];

    //Unproject the near and far plane points to build a world space ray
    glm::mat4 invViewProj = glm::inverse(camera->projectionMatrix * camera->viewMatrix);
    glm::vec4 nearPoint = invViewProj * glm::vec4(ndcX, ndcY, -1.0f, 1.0f);
    glm::vec4 farPoint = invViewProj * glm::vec4(ndcX, ndcY, 1.0f, 1.0f);
    nearPoint /= nearPoint.w;
    farPoint /= farPoint.w;

    glm::vec3 rayOrigin = glm::vec3(nearPoint);
    glm::vec3 rayDir = glm::normalize(glm::vec3(farPoint - nearPoint));

    Entity* closest = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for (const Pickable& p : pickables)
    {
        if (!p.mesh->owner)
            continue;

        Transform* transform = p.mesh->owner->TryGetComponent<Transform>();
        if (!transform)
            continue;

        //Test in the mesh's local space so rotation and scale are handled
        glm::mat4 invModel = glm::inverse(transform->modelMatrix);
        glm::vec3 localOrigin = glm::vec3(invModel * glm::vec4(rayOrigin, 1.0f));
        glm::vec3 localDir = glm::vec3(invModel * glm::vec4(rayDir, 0.0f));

        float t;
        if (!RayIntersectsAABB(localOrigin, localDir, p.localMin, p.localMax, t))
            continue;

        //Compare hit distances in world space, local t values are not comparable between objects
        glm::vec3 worldHit = glm::vec3(transform->modelMatrix * glm::vec4(localOrigin + localDir * t, 1.0f));
        float distance = glm::length(worldHit - rayOrigin);

        if (distance < closestDistance)
        {
            closestDistance = distance;
            closest = p.mesh->owner;
        }
    }

    return closest;
}
