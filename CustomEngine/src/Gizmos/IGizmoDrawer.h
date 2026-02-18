#pragma once
#include "ECS/Entity.h"

class IGizmoDrawer {
public:
    virtual ~IGizmoDrawer() = default; // virtual destructor
    virtual void DrawGizmos(Entity* entity) = 0; // public pure virtual
};
