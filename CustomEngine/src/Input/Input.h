#pragma once
#include "IInputDevice.h"
#include <vector>
#include <glm/vec2.hpp>
#include <memory>

class Input {
public:
    static glm::vec2 GetPointerPosition();
    static void SetPointerPosition(glm::vec2 position);

private:

    static inline glm::vec2 pointerPosition;
};
