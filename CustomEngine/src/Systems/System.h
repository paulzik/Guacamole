#pragma once
#include "ECS/Component.h"

class System{
public:
    virtual ~System() = default;
    virtual void TryRegister(Component*) {}
    
    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual void Shutdown() = 0;
};