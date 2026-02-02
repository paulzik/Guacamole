#include "CameraSystem.h"
#include "Scene.h"
#include "Transform.h"

void CameraSystem::TryRegister(Component* c)
{
    if (!mainCamera)
        if (auto cam = dynamic_cast<Camera*>(c))
            mainCamera = cam;
}

bool CameraSystem::Init()
{
	return true;
}

void CameraSystem::Update()
{
    if (!mainCamera)
        return;

    Transform& transformComp = mainCamera->owner->GetComponent<Transform>();

    glm::quat q = transformComp.rotation;
    glm::vec3 cameraFwd = glm::normalize(q * glm::vec3(0, 0, -1));
    mainCamera->forward = cameraFwd;
    
    glm::vec3 cameraPos = transformComp.position;
    mainCamera->lookAtVector = cameraPos + mainCamera->forward;

    mainCamera->viewMatrix = glm::lookAt(
        cameraPos,
        mainCamera->lookAtVector,
        mainCamera->upVector
    );

    mainCamera->projectionMatrix = glm::perspective(mainCamera->fov, mainCamera->aspect, mainCamera->nearPlane, mainCamera->farPlane);
}

void CameraSystem::Shutdown()
{
}
