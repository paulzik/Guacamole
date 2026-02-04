#pragma once
#include "IInputDevice.h"

class Keyboard : public IInputDevice {
public:
    void Init() override;
    void Update() override;
    void ProcessEvent(const SDL_Event* e) override;

private:
    bool keys[256]{};
};
