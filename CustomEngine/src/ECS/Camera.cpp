#include "Camera.h"
#include "ECS/Entity.h"
#include "ECS/Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "glm/mat4x4.hpp"
#include "ECS/Scene.h"

Camera::Camera(glm::vec3 lookAt) : lookAtVector(lookAt) {
    Scene::Get().AddCamera(this);
}

Camera::~Camera() {

}

const char* Camera::GetComponentName() const {
	return "Camera";
}

glm::mat4 Camera::getViewMatrix()
{
	viewMatrix = glm::lookAt(
        owner->GetComponent<Transform>().getPosition(),              // camera position
        lookAtVector,                                                // look at
        upVector                                                    // up
    );

	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
    projectionMatrix = glm::perspective(fov, aspect, nearPlane, farPlane);

    return projectionMatrix;
}

void Camera::setLookAtVector(glm::vec3 lookAt)
{
    lookAtVector = lookAt;
}

void Camera::setUpVector(glm::vec3 up)
{
    upVector = up;
}


