#pragma once
#include "IInputDevice.h"
#include <glm/vec2.hpp>

class MouseInputDevice : public IInputDevice {
public:

	void Init() override;
	void Update() override;

	glm::vec2 GetPosition();

private:
	glm::vec2 position;

	glm::vec2 prevPosition;
};
