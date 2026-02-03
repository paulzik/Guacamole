#pragma once
#include "IInputDevice.h"

class Keyboard : public IInputDevice {
public:
    void Init() override;
    void Update() override;

private:
    bool keys[256]{};
};
