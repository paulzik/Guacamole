#include "Input.h"

glm::vec2 Input::GetPointerPosition()
{
    return pointerPosition;
}

void Input::SetPointerPosition(glm::vec2 position)
{
    pointerPosition = position;
}
