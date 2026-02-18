#pragma once
#include "Gizmos/IGizmoDrawer.h"

class TransformGizmoDrawer : public IGizmoDrawer
{
public:
    void DrawGizmos(Entity* entity) override;
};
