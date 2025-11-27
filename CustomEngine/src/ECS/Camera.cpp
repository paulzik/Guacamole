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

glm::mat4 Camera::GetViewMatrix()
{
	viewMatrix = glm::lookAt(
        owner->GetComponent<Transform>().GetPosition(),              // camera position
        lookAtVector,                                                // look at
        upVector                                                    // up
    );

	return viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    projectionMatrix = glm::perspective(fov, aspect, nearPlane, farPlane);

    return projectionMatrix;
}

void Camera::SetLookAtVector(glm::vec3 lookAt)
{
    lookAtVector = lookAt;
}

void Camera::SetUpVector(glm::vec3 up)
{
    upVector = up;
}

float Camera::GetFov()
{
    return glm::degrees(fov);
}

void Camera::SetFov(float degrees)
{
    fov = glm::radians(degrees);
}

float Camera::GetNearPlane()
{
    return nearPlane;
}

void Camera::SetNearPlane(float np)
{
    nearPlane = np;
}

float Camera::GetFarPlane()
{
    return farPlane;
}

void Camera::SetFarPlane(float fp)
{
    farPlane = fp;
}


