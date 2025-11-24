#pragma once
#include "Component.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/quaternion.hpp"

class Transform : public Component {
private:
	glm::mat4 modelMatrix;

	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::quat rotation = glm::quat();
	glm::vec3 scale = glm::vec3(1,1,1);

public:
	Transform(glm::vec3 pos);
	~Transform();

	glm::vec3 getPosition();
	const char* GetComponentName() const override;

	void setPosition(glm::vec3 pos);
	void setRotation(float angle, glm::vec3 axis);
	void setScale(glm::vec3 sc);
	
	glm::mat4 getModelMatrix();
};