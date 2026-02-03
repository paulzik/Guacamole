#include "Input.h"

void Input::Init()
{
    for (auto& [_, device] : devices)
        device->Init();
}

void Input::Update()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        // forward event to every device
        for (auto& [_, device] : devices)
            device->ProcessEvent(e);
    }

    for (auto& [_, device] : devices)
        device->Update();
}
