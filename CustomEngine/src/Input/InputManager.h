#pragma once
#include "IInputDevice.h"
#include <vector>
#include <glm/vec2.hpp>
#include <memory>

class InputManager {
public:
    void Init();
    void Update();

private:

    std::vector<std::unique_ptr<IInputDevice>> devices;
};
