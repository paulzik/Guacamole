#pragma once
#include "Component.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/quaternion.hpp"

struct Transform : public Component {
	glm::mat4 modelMatrix;
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::quat rotation = glm::quat();
	glm::vec3 scale = glm::vec3(1,1,1);

	glm::vec3 up = glm::vec3(0, 0, -1);

	COMPONENT_NAME(Transform);
};