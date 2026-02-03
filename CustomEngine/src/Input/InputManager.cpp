#include "InputManager.h"
#include "MouseInputDevice.h"
#include "KeyboardInputDevice.h"

void InputManager::Init()
{
	devices.push_back(std::make_unique<MouseInputDevice>());
	devices.push_back(std::make_unique<KeyboardInputDevice>());

	for (auto& device : devices) {
		device->Init();
	}
}

void InputManager::Update()
{
	for (auto& device : devices) {
		device->Update();
	}
}