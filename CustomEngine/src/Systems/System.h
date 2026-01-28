#pragma once

class System{
public:
    virtual ~System() = default;
    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual void Shutdown() = 0;
};