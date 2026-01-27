#pragma once

class System{
public:
    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual void Shutdown() = 0;
};