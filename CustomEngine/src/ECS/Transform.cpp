#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>

Transform::Transform(glm::vec3 pos)
	: position(pos), rotation(glm::quat()), scale(1, 1, 1)
{
}

Transform::~Transform() {

}

glm::vec3 Transform::GetPosition() 
{
	return position;
}

glm::quat Transform::GetRotationQuat() 
{
	return rotation;
}

glm::vec3 Transform::GetRotationEuler()
{
	return glm::eulerAngles(rotation);
}


glm::vec3 Transform::GetScale()
{
	return scale;
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