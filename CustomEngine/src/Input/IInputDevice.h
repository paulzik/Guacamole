#pragma once
#include "SDL3/SDL_events.h"

class IInputDevice {
public:
    virtual ~IInputDevice() = default;
    virtual void ProcessEvent(const SDL_Event& e) = 0;
    virtual void Init() = 0;
    virtual void Update() = 0;
};
