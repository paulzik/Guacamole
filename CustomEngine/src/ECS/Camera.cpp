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

glm::vec3 Camera::GetLookAt() const
{
    return  owner->GetComponent<Transform>().GetPosition() + forward;
}

void Camera::SetForward(glm::vec3 dir)
{
    forward = glm::normalize(dir);
}

void Camera::Move(glm::vec3 delta)
{
    glm::vec3 pos = owner->GetComponent<Transform>().GetPosition();
    pos += delta;
    owner->GetComponent<Transform>().SetPosition(pos);

    lookAtVector = pos + forward;
}

void Camera::Update()
{
    Transform& transform = owner->GetComponent<Transform>();

    glm::vec3 position = transform.GetPosition();
    forward = GetForwardFromRotation();

    lookAtVector = position + forward;
}

glm::vec3 Camera::GetForwardFromRotation()
{
    glm::quat q = owner->GetComponent<Transform>().GetRotationQuat();

    return glm::normalize(q * glm::vec3(0, 0, -1));
}


