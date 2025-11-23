#pragma once
#include "Component.h"
#include "glm/vec3.hpp"

class Transform : public Component {
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

public:
	Transform(glm::vec3 pos);
	~Transform();

	glm::vec3 GetPosition();
	const char* GetComponentName() const override;
};