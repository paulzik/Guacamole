#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>

Transform::Transform(glm::vec3 pos)
	: position(pos), rotation(glm::quat()), scale(1, 1, 1)
{
}

Transform::~Transform() {

}

glm::vec3 Transform::getPosition() 
{
	return position;
}

void Transform::setPosition(glm::vec3 pos)
{
	position = pos;
}

void Transform::setRotation(float angle, glm::vec3 axis)
{
	rotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
}

void Transform::setScale(glm::vec3 sc)
{
	scale = sc;
}

glm::mat4 Transform::getModelMatrix()
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