#pragma once
#include "ECS/Entity.h"

class IGizmoDrawer {
public:
    virtual ~IGizmoDrawer() = default;
    virtual void DrawGizmos(Entity* entity) = 0;
};
