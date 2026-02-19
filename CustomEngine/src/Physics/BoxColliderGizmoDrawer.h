#pragma once
#include "Gizmos/IGizmoDrawer.h"

class BoxColliderGizmoDrawer : public IGizmoDrawer
{
public:
    void DrawGizmos(Entity* entity) override;
};
