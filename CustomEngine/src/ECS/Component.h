#pragma once
#include "ComponentMacros.h"
#include "IFieldVisitor.h"

class Entity;

struct Component {
    int componentID;
    Entity* owner = nullptr;

    Component();
    virtual ~Component() = default;

    virtual void Start();
    virtual void Update();

    virtual const char* GetComponentName() const = 0;

    // Names this component's serializable fields.
    virtual void Reflect(IFieldVisitor& visitor) {}
};

