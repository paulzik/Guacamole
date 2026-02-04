#pragma once
#include <glm/vec2.hpp>
#include "IInputDevice.h"
#include "ButtonControll.h"
#include "AxisControll.h"

class Mouse : public IInputDevice {
public:
	void Init() override;
	void Update() override;

	void ProcessEvent(const SDL_Event* e) override;
	glm::vec2 position;

	ButtonControll leftButton;
	ButtonControll rightButton;
	ButtonControll middleButton;

	AxisControll scrollWheel;
};
