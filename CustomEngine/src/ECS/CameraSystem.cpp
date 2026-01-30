#include "CameraSystem.h"
#include "Scene.h"
#include "Transform.h"

bool CameraSystem::Init()
{
	return false;
}

void CameraSystem::Update()
{
    Camera* camera = Scene::Get().GetCamera();
    const auto transformComp = camera->owner->GetComponent<Transform>();

    glm::quat q = transformComp.rotation;
    glm::vec3 cameraFwd = glm::normalize(q * glm::vec3(0, 0, -1));
    camera->forward = cameraFwd;
    
    glm::vec3 cameraPos = transformComp.position;
    camera->lookAtVector = cameraPos + camera->forward;

    camera->viewMatrix = glm::lookAt(
        cameraPos,
        camera->lookAtVector,
        camera->upVector
    );

    camera->projectionMatrix = glm::perspective(camera->fov, camera->aspect, camera->nearPlane, camera->farPlane);
}

void CameraSystem::Shutdown()
{
}
