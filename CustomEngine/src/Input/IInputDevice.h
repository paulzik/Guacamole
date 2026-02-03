#pragma once

class IInputDevice {
public:
    virtual ~IInputDevice() = default;
    virtual void Init() = 0;
    virtual void Update() = 0;
};
