#pragma once
#include "Gizmos/IGizmoDrawer.h"

class ColliderGizmoDrawer : public IGizmoDrawer
{
public:
    void DrawGizmos(Entity* entity) override;
};
