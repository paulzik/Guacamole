#include "Input.h"

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

bool Input::SDL3_ProcessEvent(const SDL_Event* event)
{
    for (auto& [_, device] : devices)
        device->ProcessEvent(event);

    return true;
}
