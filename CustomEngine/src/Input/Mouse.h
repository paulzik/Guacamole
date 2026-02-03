#pragma once
#include "IInputDevice.h"
#include <glm/vec2.hpp>

class Mouse : public IInputDevice {
public:
	void Init() override;
	void Update() override;

	glm::vec2 GetPosition();

private:
	bool left = false;
	bool middle = false;
	bool right = false;
	int scrollX = 0;
	int scrollY = 0;

	glm::vec2 position;
	glm::vec2 prevPosition;
};
