#pragma once
#include "ECS/Component.h"

class System{
public:
    virtual ~System() = default;
    virtual void TryRegister(Component*) {}

    // Counterpart to TryRegister: drop every reference to this component.
    // Called before the component is destroyed, so systems never keep a
    // dangling pointer. Must be safe to call for components a system never
    // registered.
    virtual void TryUnregister(Component*) {}
    
    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual void Shutdown() = 0;
};