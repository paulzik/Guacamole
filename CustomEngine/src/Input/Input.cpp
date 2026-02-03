#include "Input.h"

glm::vec2 Input::GetPointerPosition()
{
    return pointerPosition;
}

glm::vec2 Input::GetPointerDelta()
{
    return pointerDelta;
}

void Input::SetPointerPosition(glm::vec2 position)
{
    pointerPosition = position;
}

void Input::SetPointerDelta(glm::vec2 delta)
{
    pointerDelta = delta;
}

void Input::Init()
{
    for (auto& [_, device] : devices)
        device->Init();
}

void Input::Update()
{
    for (auto& [_, device] : devices)
        device->Update();
}
