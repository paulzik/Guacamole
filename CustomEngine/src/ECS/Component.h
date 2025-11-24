#pragma once
class Entity;

class Component {
protected:
    int componentID;
    Entity* owner = nullptr;

public:
    Component();
    virtual ~Component();

    virtual void Start();
    virtual void Update();

    virtual const char* GetComponentName() const = 0;

    void setOwner(Entity* _owner);
    Entity* getOwner();
};
