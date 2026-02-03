#pragma once

class ButtonControll{
public:
	bool isPressed = false;
	bool isReleased = false;

	bool wasPressedThisFrame = false;
	bool wasReleasedThisFrame = false;

	bool prevIsPressed = false;
};
