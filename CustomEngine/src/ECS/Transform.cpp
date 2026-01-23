#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>

Transform::Transform(glm::vec3 pos)
	: position(pos), rotation(glm::quat()), scale(1, 1, 1)
{
}

Transform::~Transform() {

}

glm::vec3 Transform::GetPosition() const
{
	return position;
}

glm::quat Transform::GetRotationQuat() const
{
	return rotation;
}

glm::vec3 Transform::GetRotationEuler() const
{
	return glm::eulerAngles(rotation);
}


glm::vec3 Transform::GetScale() const
{
	return scale;
}

glm::vec3 Transform::GetForward() const
{
	return glm::normalize(rotation * up);
}

glm::vec3 Transform::GetUp() const
{
	return up;
}

void Transform::SetPosition(glm::vec3 pos)
{
	position = pos;
}

void Transform::SetRotation(float angle, glm::vec3 axis)
{
	rotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
}

void Transform::SetRotation(glm::quat quat)
{
	rotation = quat;
}

void Transform::SetRotation(glm::vec3 euler)
{
	rotation = glm::quat(euler);
}

void Transform::SetScale(glm::vec3 sc)
{
	scale = sc;
}

glm::mat4 Transform::GetModelMatrix()
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix *= glm::mat4_cast(rotation);
	modelMatrix = glm::scale(modelMatrix, scale);

    return modelMatrix;
}


const char* Transform::GetComponentName() const
{
	return "Transform";
}