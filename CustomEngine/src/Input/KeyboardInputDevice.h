#pragma once
#include "IInputDevice.h"

class KeyboardInputDevice : public IInputDevice {
public:
    void Init() override;
    void Update() override;

private:
    bool keys[256]{};
};
