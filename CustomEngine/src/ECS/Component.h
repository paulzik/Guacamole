#pragma once
#include "ComponentMacros.h"

class Entity;

struct Component {
    int componentID;
    Entity* owner = nullptr;

    Component();
    virtual ~Component();

    virtual void Start();
    virtual void Update();
    virtual void Destroy();

    virtual const char* GetComponentName() const = 0;

    void setOwner(Entity* _owner);
    Entity* getOwner();
};
