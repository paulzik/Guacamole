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

	glm::vec3 GetPosition();
	glm::quat GetRotationQuat();
	glm::vec3 GetRotationEuler();
	glm::vec3 GetScale();

	glm::vec3 GetForward() const;

	const char* GetComponentName() const override;

	void SetPosition(glm::vec3 pos);
	void SetRotation(float angle, glm::vec3 axis);
	void SetRotation(glm::quat quat);
	void SetRotation(glm::vec3 euler);
	void SetScale(glm::vec3 sc);
	
	glm::mat4 GetModelMatrix();
};